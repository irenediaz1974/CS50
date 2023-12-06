import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from flask import url_for
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    if request.method == "POST":
       """Show portfolio of stocks """
       result = db.execute("SELECT * FROM stocks WHERE user_id= ? ", session["user_id"])
         # Add price and name actual to the user stocks
       rows_result=[]
       for row in result:
            stocks_data={"symbol": row["symbol"], "shares": row["shares"]}
            symbol_dict = lookup(row["symbol"])
            if symbol_dict:
               stocks_data.update(symbol_dict)
               rows_result.append(stocks_data)
             # Open portfolio page (index.html)
               return render_template("index.html", rows=rows_result)
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("index.html")



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        #TODO: Revisar si lo que esta escrito en shares es correcto, sino apology
         if not request.form.get("shares"):
            return apology("missing shares", 400)
            #TODO: Ensure the user have cash by consulting users table and calculate sharesxprice
            row = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
            cash = int(row[0]["cash"])
            stock=lookup(request.form.get("symbol"))
            # mostrar portfolio de stoks por user index and send flash message
            flash("Bought!")
            return redirect(url_for('index'))
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
  # User reached quote via POST
    if request.method == "POST":
     # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("Missing symbol", 400)
        else:
            symbol_data= lookup(request.form.get("symbol"))
            if not symbol_data:
                 return apology("Invalid Symbol", 400)
            else:
                return render_template("quoted.html", symbol=symbol_data["name"], price=symbol_data["price"])
    if request.method == "GET":
        return render_template("quoted.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    # Forget any user_id
    session.clear()
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        dict={"username": request.form.get("username"), "password":request.form.get("password"), "confirmation": request.form.get("confirmation")}
        for key in dict:
            if not dict[key]:
                 return apology(f"must provide {key}", 403)
        if request.form.get("confirmation")!= request.form.get("password"):
            return apology("password don't match", 400)
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        # Ensure username not exists in database
        if len(rows) >= 1:
            flash('Username is not available')
            return redirect("/register")
        else:
            # Insert username and password into database
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))
            last_id = db.execute("SELECT last_insert_rowid()")[0]["last_insert_rowid()"]
            session["user_id"] = last_id
            # abrir sesion y mostrar portfolio de stoks por user index function
            flash("Registered!")
            return redirect(url_for('index'))
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
