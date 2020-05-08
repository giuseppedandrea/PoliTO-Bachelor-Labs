<!DOCTYPE html>
<html lang="it" dir="ltr">
    <head>
        <meta charset="utf-8">
        <title>Punto 1 - Richiesta</title>
    </head>
    <body>
        <h1>Ricerca lezioni corso</h1>
        <form action="punto1_risultato.php" method="post">
            Codice corso:
            <select name="codice_corso">
                <?php
                // Connessione a MySQL
                $con = mysqli_connect('localhost', 'root', '', 'PALESTRA');
                if (mysqli_connect_errno()) {
                    die('Failed to connect to MySQL: '.mysqli_connect_error());
                }
                mysqli_set_charset($con,"utf8");

                // Query
                $sql = "SELECT CodC
                        FROM CORSI
                        ORDER BY CodC";

                $result = mysqli_query($con, $sql);

                if (! $result) {
                    die('Query error: '.mysqli_error($con));
                }

                // Opzioni select
                if (mysqli_num_rows($result) > 0) {
                    while ($row = mysqli_fetch_row($result)) {
                        echo '<option value="'.$row[0].'">'.$row[0].'</option>';
                    }
                }

                // Chiusura connessione
                mysqli_close($con);
                ?>
            </select>
            <input type="submit" value="Cerca">
        </form>
    </body>
</html>
