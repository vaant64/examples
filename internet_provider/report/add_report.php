<?php
    include '../include/db_connect.php';

    $year = $_GET['year'];
    $month = $_GET['month'];

    $sql = "SELECT *
            FROM `internet_provider`.`report`
            WHERE R_Year = $year AND R_Month = $month;";

    try {
        $result = $pdo->query($sql);
    } catch(PDOException $e) {
        echo "Ошибка выполнения запроса. Возможно были введены некорректные данные!";
        include 'out_add_report.html';
        exit();
    }

    $rownumb = $result->rowcount();

    if ($rownumb) {
        echo "Такой отчёт уже существует!";
    } else {
        $pdo->exec("CALL `internet_provider`.`Add_report`($year, $month)");

        try {
            $result = $pdo->query($sql);
        } catch(PDOException $e) {
            echo "Ошибка выполнения запроса. Возможно были введены некорректные данные!";
            include 'out_add_report.html';
            exit();
        }

        $rownumb = $result->rowcount();
        if ($rownumb) {
            echo "Отчёт успешно создан!";
        } else {
            echo "Данные отсутствуют!";
        }
    }

    include 'out_add_report.html';
?>