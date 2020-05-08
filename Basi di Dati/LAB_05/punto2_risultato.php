<!DOCTYPE html>
<html lang="it" dir="ltr">
    <head>
        <meta charset="utf-8">
        <title>Punto 2 - Risultato</title>
    </head>
    <body>
        <?php
        // Controllo parametri POST
        if (! isset($_REQUEST["codice_istruttore"]) ||
            ! isset($_REQUEST["giorno"]) ||
            ! isset($_REQUEST["ora_inizio"]) ||
            ! isset($_REQUEST["durata"]) ||
            ! isset($_REQUEST["codice_corso"]) ||
            ! isset($_REQUEST["sala"])) {
            die('Inserire tutti i dati richiesti');
        }
        $codice_istruttore = $_REQUEST["codice_istruttore"];
        $giorno = $_REQUEST["giorno"];
        $ora_inizio = $_REQUEST["ora_inizio"];
        $durata = $_REQUEST["durata"];
        $codice_corso = $_REQUEST["codice_corso"];
        $sala = $_REQUEST["sala"];

        if ($durata > 60) {
            die('Il campo "Durata" deve essere minore o uguale a 60');
        }

        if ($giorno != 'Lunedì' &&
            $giorno != 'Martedì' &&
            $giorno != 'Mercoledì' &&
            $giorno != 'Giovedì' &&
            $giorno != 'Venerdì' &&
            $giorno != 'Sabato' &&
            $giorno != 'Domenica') {
            die('Il campo "Giorno" deve essere un giorno della settimana');
        }

        // Connessione a MySQL
        $con = mysqli_connect('localhost', 'root', '', 'PALESTRA');
        if (mysqli_connect_errno()) {
            die('Failed to connect to MySQL: '.mysqli_connect_error());
        }
        mysqli_set_charset($con,"utf8");

        // Query SQL
        mysqli_autocommit($con, false);
        mysqli_begin_transaction($con);

        $sql = "SELECT *
                FROM PROGRAMMA
                WHERE CodC='$codice_corso' AND
                      Giorno='$giorno'";

        $result = mysqli_query($con, $sql);
        $error = mysqli_error($con);

        if (! $result) {
            mysqli_rollback($con);
            die('Query error: '.$error);
        }

        if (mysqli_num_rows($result) > 0) {
            echo "<p>È in programma un'altra lezione per il corso $codice_corso nel giorno $giorno.</p>";
            mysqli_rollback($con);
        } else {
            $sql = "INSERT INTO PROGRAMMA(CodFisc, Giorno, OraInizio, Durata, Sala, CodC)
                    VALUES ('$codice_istruttore', '$giorno', '$ora_inizio', '$durata', '$sala', '$codice_corso')";

            $result = mysqli_query($con, $sql);
            $error = mysqli_error($con);

            if (! $result) {
                mysqli_rollback($con);
                die('Query error: '.$error);
            } else {
                mysqli_commit($con);
                echo "<p>La lezione è stata inserita nel programma dei corsi.</p>";
            }
        }

        // Chiusura connessione
        mysqli_close($con);
        ?>

        <br>

        <form action="punto2_richiesta.php" method="post">
            <input type="submit" value="Effettua un altro inserimento">
        </form>
    </body>
</html>
