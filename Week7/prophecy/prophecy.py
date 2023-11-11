# Searches database roster for poblate houses, assignments

import csv

from cs50 import SQL

# Open database
db = SQL("sqlite:///roster.db")

# Fill houses
db.execute("DELETE FROM houses")
rows_houses = db.execute("SELECT house,head FROM students_copy GROUP BY house")

for row in rows_houses:
    db.execute("INSERT INTO houses (house_name, house_head) VALUES (:house, :head)", house=row['house'], head=row['head'])

# fill assignments
db.execute("DELETE FROM assignments")
rows = db.execute("SELECT DISTINCT students_copy.id AS student_id, houses.id AS house_id FROM students_copy JOIN houses ON students_copy.house= houses.house_name")

for row in rows:
    db.execute("INSERT INTO assignments (students_id, house_id) VALUES (:student_id, :house_id)", student_id=row['student_id'],
                 house_id=row['house_id'])
