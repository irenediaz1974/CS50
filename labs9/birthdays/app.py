import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session,url_for

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/delete", methods=["POST"])
def delete():
# Configure delete button to delete by name
    delname=request.form.get("delname")
    row= db.execute("SELECT name FROM birthdays WHERE name=?", delname)
    if row is not None and len(row) > 0:
        db.execute("DELETE FROM birthdays WHERE name=?", delname)

    return redirect("/")


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # Add the user's entry into the database
        name = request.form.get("fname")
        month = request.form.get("month")
        day = request.form.get("day")
        # Avoid month or day are anything but numbers to insert into database
        if day.isdigit() and (1 <= int(day) <= 31)\
            and month.isdigit() and (1 <= int(month) <=12 ):

            try:
                db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
            except Exception as e:
                return redirect(url_for('index', error='An error occurred'))
        else:
                return redirect(url_for('index', error='Not numeric values'))

        return redirect("/")

    else:
        result = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", rows=result)

