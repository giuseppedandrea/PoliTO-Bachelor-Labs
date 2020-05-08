SET storage_engine=InnoDB;
SET FOREIGN_KEY_CHECKS=1;
use palestra;

-- Insert data
INSERT INTO Istruttore (CodFisc,Nome,Cognome,DataNascita,Email, Telefono)
VALUES ('SMTPLA80N31B791Z','Paul','Smith','1980-12-31','p.smith@email.it',NULL);
INSERT INTO Istruttore (CodFisc,Nome,Cognome,DataNascita,Email, Telefono)
VALUES ('KHNJHN81E30C455Y','John','Johnson','1981-05-30','j.johnson@email.it','+2300110303444');
INSERT INTO Istruttore (CodFisc,Nome,Cognome,DataNascita,Email, Telefono)
VALUES ('AAAGGG83E30C445A','Peter','Johnson','1981-05-30','p.johnson@email.it','+2300110303444');
INSERT INTO Corsi (CodC,Nome,Tipo,Livello)
VALUES ('CT100','Spinning principianti','Spinning ',1);
INSERT INTO Corsi (CodC,Nome,Tipo,Livello)
VALUES ('CT101','Ginnastica e musica','Attività musicale',2);
INSERT INTO Corsi (CodC,Nome,Tipo,Livello)
VALUES ('CT104','Spinning professionisti','Spinning',4);
INSERT INTO Programma (CodFisc,Giorno,OraInizio,Durata,Sala,CodC)
VALUES ('SMTPLA80N31B791Z','Lunedì','10:00',45,'S1','CT100');
INSERT INTO Programma (CodFisc,Giorno,OraInizio,Durata,Sala,CodC)
VALUES ('SMTPLA80N31B791Z','Martedì','11:00',45,'S1','CT100');
INSERT INTO Programma (CodFisc,Giorno,OraInizio,Durata,Sala,CodC)
VALUES ('SMTPLA80N31B791Z','Martedì','15:00',45,'S2','CT100');
INSERT INTO Programma (CodFisc,Giorno,OraInizio,Durata,Sala,CodC)
VALUES ('KHNJHN81E30C455Y','Lunedì','10:00',30,'S2','CT101');
INSERT INTO Programma (CodFisc,Giorno,OraInizio,Durata,Sala,CodC)
VALUES ('KHNJHN81E30C455Y','Lunedì','11:30',30,'S2','CT104');
INSERT INTO Programma (CodFisc,Giorno,OraInizio,Durata,Sala,CodC)
VALUES ('KHNJHN81E30C455Y','Mercoledì','9:00',60,'S1','CT104');

