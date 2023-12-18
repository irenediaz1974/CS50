import os
from flask import Flask, flash, redirect, render_template, request
from flask import url_for
from helpers import apology, lookup

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd


# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET"])

def index():

    return render_template(
        "index.html"
    )
