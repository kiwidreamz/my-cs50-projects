SELECT DISTINCT name FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id WHERE movies.id IN
(SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id WHERE (SELECT people.id WHERE people.name = "Kevin Bacon" AND people.birth = 1958) = stars.person_id
)
AND people.name != "Kevin Bacon";