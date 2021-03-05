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
        echo "������ ���������� �������. �������� ���� ������� ������������ ������!";
        include 'out_add_report.html';
        exit();
    }

    $rownumb = $result->rowcount();

    if ($rownumb) {
        echo "����� ����� ��� ����������!";
    } else {
        $pdo->exec("CALL `internet_provider`.`Add_report`($year, $month)");

        try {
            $result = $pdo->query($sql);
        } catch(PDOException $e) {
            echo "������ ���������� �������. �������� ���� ������� ������������ ������!";
            include 'out_add_report.html';
            exit();
        }

        $rownumb = $result->rowcount();
        if ($rownumb) {
            echo "����� ������� ������!";
        } else {
            echo "������ �����������!";
        }
    }

    include 'out_add_report.html';
?>