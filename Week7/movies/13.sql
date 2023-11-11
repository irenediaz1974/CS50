SELECT people.name FROM people
  WHERE NOT people.name= "Kevin Bacon"
  AND people.id IN (SELECT person_id
	FROM stars WHERE movie_id IN
	(SELECT movie_id FROM people p
		JOIN stars s
		ON p.id=s.person_id
		 AND p.name= "Kevin Bacon" AND birth= 1958
		JOIN movies m
		ON m.id=s.movie_id));
