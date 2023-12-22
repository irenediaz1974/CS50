import os
from flask import Flask, flash, redirect, render_template, request
from flask import url_for
import requests
from bs4 import BeautifulSoup
#from helpers import apology, lookup

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

@app.route("/", methods=["GET"])

def index():
    
    if request.method == "POST":
        url = request.form["url"]
        estadisticas = obtener_estadisticas(url)
        return render_template("index.html", 
                               titulo="Mi sitio web",
                               contenido="Este es el contenido de la página de inicio.",
                               seccion_izquierda=render_template("sidebar.html",
                               estadisticas=estadisticas))
    else:
        return render_template("index.html",
                               titulo="Mi sitio web",
                               contenido="Este es el contenido de la página de inicio.",
                               seccion_izquierda=render_template("sidebar.html"))


@app.route("/sidebar")
def sidebar():
    return render_template("sidebar.html")

if __name__ == "__main__":
    app.run(debug=True)




def obtener_estadisticas(url):
    respuesta = requests.get(url)
    soup = BeautifulSoup(respuesta.content, "html.parser")

    titulo = soup.find("title").text
    palabras_clave = soup.find_all("meta", {"name": "keywords"})
    descripcion = soup.find_all("meta", {"name": "description"})

    return {
        "titulo": titulo,
        "palabras_clave": palabras_clave,
        "descripcion": descripcion
    }

if __name__ == "__main__":
    url = input("Ingrese la URL: ")
    estadisticas = obtener_estadisticas(url)

    print("Título:", estadisticas["titulo"])
    print("Palabras clave:", estadisticas["palabras_clave"])
    print("Descripción:", estadisticas["descripcion"])
