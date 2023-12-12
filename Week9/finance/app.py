import os
import datetime
import pytz
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


@app.route('/', methods=['GET'])
@login_required
def index():
    """Show portfolio of stocks """
    result = db.execute("SELECT * FROM stocks WHERE user_id= ? ", session["user_id"])
    cash_data = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    cash = int(cash_data[0]["cash"])
    # Add price and name actual to the user stocks
    rows_result=[]
    total=cash
    for row in result:
        stocks_data={"symbol": row["symbol"], "shares": int(row["shares"])}
        symbol_dict = lookup(row["symbol"])
        if symbol_dict:
            symbol_dict["price"] = int(symbol_dict["price"])
            stocks_data.update(symbol_dict)
            rows_result.append(stocks_data)
            total += stocks_data["shares"] * symbol_dict["price"]
    # Open portfolio page (index.html)
    print(rows_result)
    return render_template("index.html", rows_result=rows_result, usd=usd, cash=cash, total=total)




@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Check form data
        result = check_form_values(request.form.get("shares"), request.form.get("symbol"))

        if isinstance(result, tuple) and len(result)==3:
            shares, symbol, price = result
        else:
            return apology("error in buy", 400)

        # Ensure the user have cash by consulting users table and calculate shares x price
        row = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        cash = int(row[0]["cash"])

        if cash >= shares * price:
            #insert buy in database ( cash in users,(symbol, shares) in stocks)
            buy= buy_transaction(session["user_id"], cash, price, shares, symbol)

            if buy==1:
                 # mostrar portfolio de stoks por user index and send flash message
                 flash("Bought!")
                 return redirect(url_for('index'))
            else:
                return apology("error in transaction", 400)
        else:
            return apology("not enought cash", 400)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    rows_result= db.execute ("SELECT * FROM transactions WHERE user_id=?", session["user_id"] )
    return render_template("history.html", rows_result=rows_result)


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
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    # Forget any user_id
    session.clear()

    if request.method == "POST":
        # Check form data
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)
        password=request.form.get("password")
        if not password:
            return apology("must provide password", 400)
        confirmation= request.form.get("confirmation")
        if not confirmation:
            return apology("must provide confirmation", 400)
        if request.form.get("confirmation")!= request.form.get("password"):
            return apology("password don't match", 400)
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        # Ensure username not exists in database
        if len(rows) >= 1:
            return apology("Username Exist", 400)
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
    if request.method == "POST":
        # Check form data
        result = check_form_values(request.form.get("shares"), request.form.get("symbol"))
        if isinstance(result, tuple) and len(result)==3:
            shares, symbol, price = result
        else:
            return apology("error in buy", 400)
        # Check in database if the user has shares for symbol
        row = db.execute("SELECT shares FROM stocks WHERE user_id=? and symbol=?", session["user_id"], symbol)
        db_shares = int(row[0]["shares"])
        if db_shares >= shares:
            # do transaction
            #insert buy in database ( cash in users,(symbol, shares) in stocks)
            sell= sell_transaction(session["user_id"], shares, symbol, price)
            if sell==1:
                 # mostrar portfolio de stoks por user index and send flash message
                 flash("Sold!")
                 return redirect(url_for('index'))
            else:
                return apology("error in sell", 400)
        else:
            return apology("to much shares to sell", 400)
    else:
        return render_template("sell.html")






def buy_transaction(user_id, cash, price, shares, symbol):
     """Purchase."""
     purchase=price * shares
     day_transact= datetime.datetime.now(pytz.timezone("US/Eastern"))
     db.execute("BEGIN TRANSACTION;")
     # Actualizar la tabla de usuarios
     db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", purchase, user_id)
     # Actualizar la tabla de acciones
     try:
        db.execute("INSERT INTO stocks (user_id, symbol, shares) VALUES (?, ?, ?)", user_id, symbol, shares)
     except:
        db.execute("UPDATE stocks SET shares= shares+ ?  WHERE user_id = ? AND symbol= ?", shares, user_id, symbol)

     db.execute("INSERT INTO transactions (user_id, symbol, shares, day_transact, price_transact, is_purchase) VALUES (?, ?, ?, ?, ?, True)", user_id, symbol, shares, day_transact, price)
     db.execute("COMMIT;")
     return 1

def sell_transaction(user_id, shares, symbol, price):
     """Sell."""
     cash_t=price * shares
     day_transact= datetime.datetime.now(pytz.timezone("US/Eastern"))
     db.execute("BEGIN TRANSACTION;")
     # Actualizar la tabla de usuarios
     db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", cash_t, user_id)
     # Actualizar la tabla de acciones
     db.execute("UPDATE stocks SET shares= shares - ?  WHERE user_id = ? AND symbol= ?", shares, user_id, symbol)
     db.execute("DELETE FROM stocks  WHERE user_id = ? AND symbol= ? AND shares=0", user_id, symbol)
     db.execute("INSERT INTO transactions (user_id, symbol, shares, day_transact, price_transact, is_purchase) VALUES (?, ?, ?, ?, ?, False)", user_id, symbol, shares, day_transact, price)
     db.execute("COMMIT;")
     return 1












def check_form_values(shares, symbol):
        #TODO: Ensure shares exist and viable
        try:
            shares=int(shares)
        except:
            return apology("check shares", 400)
        if shares<= 0:
            return apology("check shares", 400)
        if not symbol:
             return apology("missing symbol", 400)
         # Obtain symbol data
        stock=lookup(symbol)
        if not stock:
            return apology("missing symbol", 400)
        #  lookup (name, price, symbol)
        price= float(stock["price"])

        return (shares, symbol, price)
