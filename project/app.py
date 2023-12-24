import os
from flask import Flask, flash, redirect, render_template, request
from flask import url_for
import requests
from bs4 import BeautifulSoup
from helpers import readability, obtener_estadisticas, apology

# Configure application
app = Flask(__name__)

# Custom filter
#app.jinja_env.filters["usd"] = usd


# Configure CS50 Library to use SQLite database
#db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        try:
            texto_analizar = request.form["textanalisis"]
            print (texto_analizar)
            # only 200 words will be consider in the readability function
            words= texto_analizar.split()
            if len(words) > 200:
                words = words[:200]
                texto_analizar = ' '.join(words)
                print(texto_analizar)
            # readability function - sentiment (week 6)
            indice= readability(texto_analizar)
            show_index = True
            return render_template("index.html", indice=indice, show_index=show_index)
        except Exception as e:
            return apology("an error occurred", e)

    else:
        return render_template("index.html")


@app.route("/estadistica", methods=["GET", "POST"])
def estadistica():
    if request.method == "POST":
        url=request.form["url"]
        try:
            response = requests.get(url)
            if response.status_code != 200:
                return apology("Revise URL", 500)
        except requests.exceptions.MissingSchema:
            return apology("Revise URL", 400)

        try:
            estadisticas=obtener_estadisticas(url)
            return render_template("sentiment.html", estadisticas)
        except:
            msg="Error en la obtención de estadisticas"
            return apology("an error occurred", 403)
    else:
            return render_template("estadistica.html")

@app.route("/sidebar")
def sidebar():
    return render_template("sidebar.html")


if __name__ == "__main__":
    app.run(debug=True)
    