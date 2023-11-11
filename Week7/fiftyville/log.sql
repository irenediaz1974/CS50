-- Keep a log of any SQL queries you execute as you solve the mystery.

--- 1. Read crime scene report
SELECT * FROM crime_scene_reports WHERE day=28 AND month=7 AND year = 2021 AND street='Humphrey Street';
/* CLUE: Theft of the CS50 duck took place at 10:15 am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.*/

-- 2. Read in Interviews the description of the witnesses related to the bakery
        --and the time of the robbery, which was at 10:15 am

SELECT * FROM interviews WHERE transcript LIKE "%bakery%" AND day=28 AND month=7;

/* Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
   Eugene: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
   Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.*/

-- 3. Find the information of the car owner who left the parking lot between 10:15 and 10:25 according to Ruth.
SELECT name,phone_number FROM bakery_security_logs b
JOIN people ON b.license_plate=people.license_plate
WHERE b.day=28 AND b.month=7 and b.hour= 10 and b.minute between 5 AND 25
ORDER BY name;

-- 4. According to Raymond, the thief made a short call....

SELECT DISTINCT name,phone_number FROM phone_calls ph
JOIN people p ON p.phone_number=ph.caller
JOIN bakery_security_logs b ON b.license_plate=p.license_plate
WHERE ph.day=28 AND ph.month=7 AND ph.duration < 60
AND b.day=28 AND b.month=7 and b.hour= 10 and b.minute BETWEEN 5 AND 25;

-- 5. According to Eugene, find who made a banking transaction on 'Leggett Street'
       --having day, month and street:


SELECT p.name,phone_number FROM bank_accounts bk
JOIN people p ON p.id=bk.person_id
JOIN atm_transactions at ON at.account_number=bk.account_number
WHERE at.atm_location='Leggett Street'
AND  at.day=28 AND at.month=7 AND at.year=2021;

--6. People who made calls lasting less than one minute and banking operations:
SELECT p.name,phone_number FROM bank_accounts bk
JOIN people p ON p.id=bk.person_id
JOIN atm_transactions at ON at.account_number=bk.account_number
JOIN bakery_security_logs b ON b.license_plate=p.license_plate
JOIN phone_calls ph ON p.phone_number=ph.caller
WHERE at.atm_location='Leggett Street'
AND  at.day=28 AND at.month=7 AND at.year=2021
AND ph.day=28 AND ph.month=7 AND ph.duration < 60
AND b.day=28 AND b.month=7 and b.hour= 10 and b.minute between 5 AND 25;

--7. Putting together all the clues of the robbery to find the thief:
SELECT DISTINCT name FROM people p
JOIN passengers pa
ON p.passport_number = pa.passport_number
JOIN bakery_security_logs as b
ON b.license_plate = p.license_plate
JOIN bank_accounts bk
ON p.id=bk.person_id
JOIN atm_transactions at
ON bk.account_number=at.account_number
JOIN phone_calls ph
ON p.phone_number=ph.caller
WHERE atm_location='Leggett Street'
AND ph.day=28 AND ph.month=7 AND ph.duration < 60
AND b.day=28 AND b.month=7 and b.hour= 10 and b.minute BETWEEN 5 AND 25
AND pa.flight_id=(SELECT flights.id FROM flights
	JOIN airports ON airports.id=flights.destination_airport_id
	WHERE day=29 AND month=7 AND year=2021 ORDER BY hour
	LIMIT 1);


--8. Already knowing who the thief is, finding who he called in less than a minute

SELECT name FROM people p
JOIN phone_calls ph
ON p.phone_number=ph.receiver
WHERE ph.day=28 AND ph.month=7 AND ph.duration < 60
AND ph.caller=
	(SELECT phone_number FROM people WHERE name='Bruce');

--9. Search destination for the earliest flight on the 29th...
SELECT full_name,city FROM flights
JOIN airports ON airports.id=flights.destination_airport_id
WHERE day=29 AND month=7 AND year=2021
ORDER BY hour
LIMIT 1;
