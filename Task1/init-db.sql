DROP database Task1;
CREATE DATABASE IF NOT EXISTS Task1;
USE Task1;

CREATE TABLE IF NOT EXISTS
users(
    id                INTEGER UNIQUE NOT NULL,
    login             TEXT NOT NULL,
    money_amount      INTEGER NOT NULL,
    card_number       TEXT NOT NULL,
    status            BOOL  NOT NULL
);

CREATE TABLE IF NOT EXISTS
passwords(
    id                INTEGER UNIQUE NOT NULL,
    password          TEXT NOT NULL
);

INSERT INTO users VALUES
        (1,'admin',123,  '4267293911235712',   true),
        (2,'Dan',  456,  '4929439296565401',  false),
        (3,'Nick', 789,  '4543532721428231',   true),
        (4,'Sam',  1011, '5497575156106460',   true),
        (5,'Pain', 121,  '4556399318894124',  false),
        (6,'Dan',  42,   '5403637094552396',   true),
        (7,'Rob',  0,    '6011641999154060',  false)

;
INSERT INTO passwords VALUES
        (1, 'qwerty'),
        (2, 'asdfgh'),
        (3, 'zxcvbn'),
        (4, 'password'),
        (5, 'root'),
        (6, '12345'),
        (7, 'aaaaaa')
;