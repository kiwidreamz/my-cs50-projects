-- Keep a log of any SQL queries you execute as you solve the mystery.

.schema
-- exploring tables and how they connect to one another

SELECT * FROM crime_scene_reports;
-- checking details about all crimes, getting the id number (295) for this crime
-- relevant information : crime took place at 10:15am on the 28th of July, there are three interview transcripts that mention the bakery where the theft took place

SELECT * FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND minute < 30 AND activity = "exit";
-- looking at security logs from that day, there are 7 different plate numbers recorded to have exited the bakery after 10:15am
-- it is safe to assume one of them belongs to the thief since the next exits happened four hours later
-- here are the 7 plates : 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

SELECT * FROM interviews WHERE day = 28 AND transcript LIKE "%bakery%";
-- looking at the interviews from that day which mention the bakery, there's four results (with id 161, 162, 163 and 193)
-- I have already checked security logs but Eugene's testimony is very interesting as he saw the thief withdraw some money right before going to the bakery
-- Raymond tells us that the thief and his/her accomplice were planning to take the earliest flight the next day, and that said accomplice purchased the ticket right away on the thief's request

SELECT * FROM atm_transactions WHERE day = 28;
-- taking a look at how the atm transactions look like and which transaction type and location to pick to refine our search

SELECT * FROM atm_transactions WHERE day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
-- Eugene saw the thieft withdraw money at Leggett Street earlier that day
-- there's no time stamp but I could compare the account numbers to the bank accounts and get names which i could then compare to people's plate numbers to see who withdrew money and then went to the bakery


SELECT people.id
    FROM people
        JOIN bakery_security_logs
        ON people.license_plate = bakery_security_logs.license_plate
    WHERE bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 30 AND bakery_security_logs.activity = "exit";
-- outputs table with people id that have the eight license plates mentionned earlier (the ones that left the bakery at 10am that day)

SELECT people.id
    FROM people
    JOIN bank_accounts
        ON people.id = bank_accounts.person_id
        JOIN atm_transactions
        ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw";
-- outputs table with people id that have withdrawn money at Leggett Street the same day as the crime happened

-- if I intersect those two earlier queries, I should get whoever is in both results

SELECT people.id
    FROM people
        JOIN bakery_security_logs
        ON people.license_plate = bakery_security_logs.license_plate
    WHERE bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 30 AND bakery_security_logs.activity = "exit"
INTERSECT
SELECT people.id
    FROM people
    JOIN bank_accounts
        ON people.id = bank_accounts.person_id
        JOIN atm_transactions
        ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw";

-- this resulted in 5 people id, which is already better than 8

SELECT * FROM phone_calls WHERE day = 28;
-- looking at the phone calls from that day, i can't do anything with it for now

SELECT * FROM flights WHERE day = 29 ORDER BY hour ASC;
-- looking at the flights the next day, i know the thief will take the earliest one, which is id 36

SELECT * FROM passengers WHERE flight_id = 36;

SELECT people.id
    FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    WHERE passengers.flight_id = 36;
-- getting people id on that flight

SELECT people.id
    FROM people
        JOIN bakery_security_logs
        ON people.license_plate = bakery_security_logs.license_plate
    WHERE bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 30 AND bakery_security_logs.activity = "exit"
INTERSECT
SELECT people.id
    FROM people
    JOIN bank_accounts
        ON people.id = bank_accounts.person_id
        JOIN atm_transactions
        ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw"
INTERSECT
SELECT people.id
    FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    WHERE passengers.flight_id = 36;
-- intersecting previous check with the passengers from the plane gives me 3 people


SELECT * FROM flights WHERE day = 29;
SELECT * FROM phone_calls WHERE day = 28;

SELECT people.id
    FROM people
    JOIN phone_calls
    ON people.phone_number = phone_calls.caller
    WHERE phone_calls.day = 28;
-- people that called someone on the 28th


SELECT people.id
    FROM people
        JOIN bakery_security_logs
        ON people.license_plate = bakery_security_logs.license_plate
    WHERE bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 30 AND bakery_security_logs.activity = "exit"
INTERSECT
SELECT people.id
    FROM people
    JOIN bank_accounts
        ON people.id = bank_accounts.person_id
        JOIN atm_transactions
        ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw"
INTERSECT
SELECT people.id
    FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    WHERE passengers.flight_id = 36
INTERSECT
SELECT people.id
    FROM people
    JOIN phone_calls
    ON people.phone_number = phone_calls.caller
    WHERE phone_calls.day = 28;
-- found him (id 686048)

SELECT * from flights
    WHERE flights.id = 36;
-- the thief escaped to airport id 4

SELECT * from airports;
-- inspecting the aiports, i see that id 4 is (LGA) LaGuardia Airport in New York City


SELECT *
    FROM people
    WHERE people.id = 686048;
-- the thief's phone numbers is "(367) 555-5533"

SELECT * from phone_calls
    WHERE phone_calls.day = 28
    AND phone_calls.caller = "(367) 555-5533";
-- the thief's made 4 calls the day of the crime but only one of them was less than 60 seconds long
-- the accomplice's phone number is (375) 555-8161


SELECT people.name
    FROM people
    WHERE people.phone_number = "(375) 555-8161";

-- the accomplice is Robin


