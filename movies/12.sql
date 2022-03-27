SELECT title FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE (SELECT people.id WHERE people.name = "Johnny Depp") = stars.person_id
INTERSECT
SELECT title FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE (SELECT people.id WHERE people.name = "Helena Bonham Carter") = stars.person_id
;