<?php
    $host = 'localhost';
    $db_name = 'internet_provider';
    $login = 'root';
    $password = '';

    try {
        $pdo = new PDO("mysql: $host; $db_name", $login, $password);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    } catch(PDOException $e) {
        echo "Îøèáêà ïîäêëþ÷åíèÿ ê áàçå äàííûõ $db_name: ", $e->getMessage();
        exit();
    }
?>
