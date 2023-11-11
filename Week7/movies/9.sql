SELECT DISTINCT name FROM stars
    JOIN people ON stars.person_id=people.id
    WHERE stars.movie_id IN (SELECT DISTINCT movies.id
    FROM movies WHERE movies.year=2004) ORDER BY people.birth;

