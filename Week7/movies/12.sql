SELECT title FROM movies m WHERE EXISTS (
    SELECT * FROM stars s JOIN people p ON s.person_id = p.id
    WHERE p.name = 'Bradley Cooper' AND s.movie_id = m.id)
AND EXISTS (
    SELECT * FROM stars s JOIN people p ON s.person_id = p.id
    WHERE p.name = 'Jennifer Lawrence' AND s.movie_id = m.id);
