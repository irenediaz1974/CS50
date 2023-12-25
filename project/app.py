import os
import glob
from flask import Flask, render_template, request
import requests
from bs4 import BeautifulSoup
from helpers import readability, obtener_estadisticas, apology, resumen

# Configure application
app = Flask(__name__)



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
        # delete old files
        for filename in glob.glob('static/img/segment*.png'):
            os.remove(filename)
        file_path = 'static/img/histogram.png'
        if os.path.exists(file_path):
            os.remove(file_path)
        url=request.form["url"]
        try:
            response = requests.get(url)
            if response.status_code != 200:
                return apology("Revise la url", 500)
        except requests.exceptions.MissingSchema:
            return apology("Revise la url", 400)
        try:
            num_words, num_segments, average_sentiment, compound_scores=obtener_estadisticas(url)
            return render_template("sentiment.html", num_words=num_words, num_segments=num_segments, average_sentiment=average_sentiment, compound_scores=compound_scores)
        except:
            return apology("Error en la obtención de estadisticas", 403)
    else:
            return render_template("estadistica.html")

@app.route("/sidebar")
def sidebar():
    return render_template("sidebar.html")


@app.route("/resumen", methods=["GET", "POST"])
def text_resumen():
    if request.method == "POST":
        try:
            if request.form["myTextarea"].strip():
                texto = request.form["myTextarea"]
                # NER function - resumen
                entidades= resumen(texto)
                show_resumen = True
                return render_template("resumen.html", entidades=entidades, show_resumen=show_resumen)
            else:
                return apology("Suministre una cadena válida", str(e))
        except Exception as e:
            return apology("an error occurred", str(e))
    else:
        return render_template("resumen.html")
