# "READABILITY". Flask Project.

#### Video Demo:  <https://youtu.be/3Pk1GdUG8XI>

## Introducción

Este proyecto está hecho en Flask y utiliza técnicas de procesamiento del lenguaje natural tales como: Extracción de Entidades Nombradas (NER) y análisis de SENTIMENT, implementadas con la biblioteca NLTK de Python y Beautiful Soup para el web scraping.
 ### Teniendo en cuenta las siguientes limitaciones:
+ NLTK: El análisis de sentimientos depende en gran medida de la calidad del modelo de aprendizaje automático que se utiliza. Los modelos preentrenados de NLTK pueden no funcionar bien con textos que contienen jerga, errores gramaticales o de ortografía, o con textos en un idioma diferente al inglés. Además, el análisis de sentimientos puede ser difícil de interpretar en textos que contienen sarcasmo o doble sentido.
+ Beautiful Soup: Esta biblioteca es excelente para extraer datos de páginas web, pero puede tener problemas con sitios web que utilizan mucho JavaScript para cargar su contenido, ya que Beautiful Soup no ejecuta JavaScript. Además, el web scraping depende de la estructura de la página web, por lo que si la página cambia su diseño, es posible que tengas que actualizar tu código de scraping.
+ La Extracción de Entidades Nombradas (NER) en NLTK se realiza utilizando el módulo ne_chunk que etiqueta los nombres propios como 'NE' (Named Entity). Primero, el texto se divide en frases, luego cada frase se divide en palabras (esto se llama tokenización), y luego cada palabra se etiqueta con su parte de discurso (por ejemplo, sustantivo, verbo, adjetivo, etc.). Finalmente, ne_chunk utiliza estas etiquetas para identificar las entidades nombradas.

> **Nota**: Esta información fue generada con la ayuda de la IA de CS50.

## Descripción
Este es un proyecto de Flask para la clase CS50x. Es una aplicacion web que permite a los usuarios realizar análisis básicos de texto.

    Menú 1: (Readability). En esta opción se hace un calculo de la legibilidad de un texto no mayor de 200 palabras utilizando la fórmula de Coleman-Liu vista en el problema Readability del curso.
    Menú 2: (Sentiment). En esta opción se realiza un web scraping de una dirección(url) suministrada por el usuario. En esta tarea se utiliza la biblioteca Beautiful Soup para analizar html en la url suministrada por el usuario (básicamente las secciones <p>) y extraer contenido para procesarlo y analizarlo con NLTK, en este caso se  calcula el sentimiento por segmentos de 1000 caracteres y el sentimiento promedio del texto.
    Luego del análisis se utiliza matplotlib para graficar un histograma de los "compound scores" de cada segmento para visualizar su variabilidad y se realiza un grafico de pie por cada segmento con los puntajes positivos, negativos y neutro para tener una vision de como se comporta el sentiment en el texto extraido.
        > **Interpretación de los puntajes de sentimiento:**
        >
        > Los puntajes compuestos varían de -1 (muy negativo) a 1 (muy positivo).
        > - Un puntaje mayor a 0.05 se puede interpretar como positivo.
        > - Un puntaje menor a -0.05 se puede interpretar como negativo.
        > - Un puntaje entre -0.05 y 0.05 se puede interpretar como neutro.


    Menú 3: (Resumen). Este menú utiliza la libreria NLTK para extraer entidades (NER) utilizando el modulo ne_chunk que etiqueta los nombres propios como 'NE' (Named Entity). Primero, el texto se divide en frases, luego cada frase se divide en palabras (esto se llama tokenización), y luego cada palabra se etiqueta con su parte de discurso (por ejemplo, sustantivo, verbo, adjetivo, etc.). Finalmente, ne_chunk utiliza estas etiquetas para identificar las entidades nombradas.

        - Es importante mencionar que NLTK puede no ser perfecto en la identificación de entidades nombradas, especialmente si el texto tiene errores gramaticales o de ortografía, o si las entidades nombradas son menos comunes o están en un idioma diferente al inglés.

## Instalación

En requirements.txt están las bibliotecas que usa este proyecto.

Instalar dependencias
```
pip install -r requirements.txt

```

Además, este proyecto utiliza NLTK, que requiere la descarga de paquetes adicionales. Puedes descargar estos paquetes con el siguiente comando en Python:

```python
import nltk
nltk.download('punkt')
nltk.download("stopwords")
nltk.download('vader_lexicon')
nltk.download('averaged_perceptron_tagger')
nltk.download('maxent_ne_chunker')
nltk.download('words')

Otras bibliotecas que se importan en el proyecto son:

```python
import os
import glob


## Uso
Esta aplicación no requiere registro, esta elaborada para CS50x por lo que es un proyecto de curso. Utiliza técnicas de web scraping. El uso de estas técnicas depende del usuario y debe realizarse de acuerdo con las leyes y los términos de servicio del sitio web objetivo. El usuario es responsable de cualquier uso del web scraping realizado a través de este proyecto.


## Contribuciones
Las contribuciones son bienvenidas. Por favor, abre un issue o un pull request si tienes algo que añadir.


## Licencia
Este proyecto está licenciado bajo la licencia MIT.

## Aviso Legal
Este proyecto utiliza técnicas de web scraping. El web scraping debe ser utilizado de manera responsable y solo en sitios web que lo permitan. El usuario de este proyecto es responsable de asegurarse de que cualquier uso del web scraping cumple con las leyes y los términos de servicio aplicables.
