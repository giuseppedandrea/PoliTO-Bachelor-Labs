<!DOCTYPE html>
<html lang="it" dir="ltr">
    <head>
        <meta charset="utf-8">
        <title>Punto 1 - Risultato</title>
    </head>
    <body>
        <?php
        // Controllo parametri POST
        if (! isset($_REQUEST["codice_corso"]) || ! isset($_REQUEST["nome_corso"]) || ! isset($_REQUEST["tipo_corso"]) || ! isset($_REQUEST["livello_corso"])) {
            die('Inserire tutti i dati richiesti');
        }
        $codice_corso = $_REQUEST["codice_corso"];
        $nome_corso = $_REQUEST["nome_corso"];
        $tipo_corso = $_REQUEST["tipo_corso"];
        $livello_corso = $_REQUEST["livello_corso"];

        if ($codice_corso=="") {
            die('Il campo "Codice" è vuoto');
        }

        if ($nome_corso=="") {
            die('Il campo "Nome" è vuoto');
        }

        if ($tipo_corso=="") {
            die('Il campo "Tipo" è vuoto');
        }

        if ($livello_corso=="") {
            die('Il campo "Livello" è vuoto');
        }

        if (! is_numeric($livello_corso)) {
            die('Il campo "Livello" deve essere un valore numerico');
        }

        if ($livello_corso < 1 || $livello_corso > 4) {
            die('Il campo "Livello" deve essere compreso tra 1 e 4');
        }

        // Connessione a MySQL
        $con = mysqli_connect('localhost', 'root', '', 'PALESTRA');
        if (mysqli_connect_errno()) {
            die('Failed to connect to MySQL: '.mysqli_connect_error());
        }
        mysqli_set_charset($con,"utf8");

        // QUERY SQL
        $sql = "INSERT INTO CORSI(CodC, Nome, Tipo, Livello) VALUES('$codice_corso', '$nome_corso', '$tipo_corso', '$livello_corso')";

        $result = mysqli_query($con, $sql);

        if ($result) {
            echo "<p>Il corso $codice_corso è stato inserito nel database.</p>";
        } else {
            die('Query error: '.mysqli_error($con));
        }

        // Chiusura connessione
        mysqli_close($con);
        ?>

        <br>

        <form action="punto1_richiesta.php" method="post">
            <input type="submit" value="Effettua un altro inserimento">
        </form>
    </body>
</html>
