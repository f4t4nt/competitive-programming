/*
Enter your query below.
Please append a semicolon ";" at the end of the query
*/
SELECT
  referrer_tld,
  COUNT( * )    AS total_events,
  SUM( amount ) AS total_amount
  FROM
    (
      SELECT
        CONCAT("*.", SUBSTRING_INDEX(referrer, '.', -2)) AS referrer_tld,
        amount
        FROM
          events
    ) t
  GROUP BY
    referrer_tld
  ORDER BY
    referrer_tld;