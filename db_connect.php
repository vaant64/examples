<?php
    $host = 'localhost';
    $db_name = 'internet_provider';
    $login = 'root';
    $password = '';

    try {
        $pdo = new PDO("mysql: $host; $db_name", $login, $password);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    } catch(PDOException $e) {
        echo "Ошибка подключения к базе данных $db_name: ", $e->getMessage();
        exit();
    }

    mysql_set_charset('windows-1251');
?>