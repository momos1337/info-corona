<?php
//coded by momos
system('clear');
system('figlet Info Corona');
echo "coded by 4LM05TH3V!L\n";
echo "Greetz: Hidden Ghost Team ~ IndoSec ~ Sorong6etar\n\n";
echo "Country   : Indonesia    \n";
$readjson = file_get_contents('https://api.kawalcorona.com/indonesia/');
$data = json_decode($readjson, true);
echo "Positif   : ";
    echo $data[0]['positif']."\n";
    echo "Sembuh    : ";
    echo $data[0]['sembuh']."\n";
    echo "Meninggal : ";
    echo $data[0]['meninggal']."\n";
    ?>
