#!/usr/bin/env bats

@test "Afficher format \"dot\" sur Canada" {
    run ../bin/run --country can --output-format dot
    [ "${lines[0]}" = "graph {" ]
    [ "${lines[1]}" = "    can [" ]
    [ "${lines[2]}" = "        shape = none," ]
    [ "${lines[3]}" = "        label = <<table border=\"0\" cellspacing=\"0\">" ]
    [ "${lines[4]}" = "            <tr><td align=\"left\" border=\"1\"><b>Name</b>: Canada</td></tr>" ]
    [ "${lines[5]}" = "            <tr><td align=\"left\" border=\"1\"><b>Code</b>: CAN</td></tr>" ]
    [ "${lines[6]}" = "        </table>>" ]
    [ "${lines[7]}" = "    ];" ]
    [ "${lines[8]}" = "}" ]
}

@test "Afficher format \"dot\" sur Canada avec --show-capital" {
    run ../bin/run --country can --output-format dot --show-capital
    [ "${lines[0]}" = "graph {" ]
    [ "${lines[1]}" = "    can [" ]
    [ "${lines[2]}" = "        shape = none," ]
    [ "${lines[3]}" = "        label = <<table border=\"0\" cellspacing=\"0\">" ]
    [ "${lines[4]}" = "            <tr><td align=\"left\" border=\"1\"><b>Name</b>: Canada</td></tr>" ]
    [ "${lines[5]}" = "            <tr><td align=\"left\" border=\"1\"><b>Code</b>: CAN</td></tr>" ]
    [ "${lines[6]}" = "            <tr><td align=\"left\" border=\"1\"><b>Capital</b>: Ottawa</td></tr>" ]
    [ "${lines[7]}" = "        </table>>" ]
    [ "${lines[8]}" = "    ];" ]
    [ "${lines[9]}" = "}" ]
}

@test "Afficher format \"dot\" sur Canada avec --show-languages" {
    run ../bin/run --country can --output-format dot --show-languages
    [ "${lines[0]}" = "graph {" ]
    [ "${lines[1]}" = "    can [" ]
    [ "${lines[2]}" = "        shape = none," ]
    [ "${lines[3]}" = "        label = <<table border=\"0\" cellspacing=\"0\">" ]
    [ "${lines[4]}" = "            <tr><td align=\"left\" border=\"1\"><b>Name</b>: Canada</td></tr>" ]
    [ "${lines[5]}" = "            <tr><td align=\"left\" border=\"1\"><b>Code</b>: CAN</td></tr>" ]
    [ "${lines[6]}" = "            <tr><td align=\"left\" border=\"1\"><b>Languages</b>: English, French</td></tr>" ]
    [ "${lines[7]}" = "        </table>>" ]
    [ "${lines[8]}" = "    ];" ]
    [ "${lines[9]}" = "}" ]
}

@test "Afficher format \"dot\" sur Canada avec --show-borders" {
    run ../bin/run --country can --output-format dot --show-borders
    [ "${lines[0]}" = "graph {" ]
    [ "${lines[1]}" = "    can [" ]
    [ "${lines[2]}" = "        shape = none," ]
    [ "${lines[3]}" = "        label = <<table border=\"0\" cellspacing=\"0\">" ]
    [ "${lines[4]}" = "            <tr><td align=\"left\" border=\"1\"><b>Name</b>: Canada</td></tr>" ]
    [ "${lines[5]}" = "            <tr><td align=\"left\" border=\"1\"><b>Code</b>: CAN</td></tr>" ]
    [ "${lines[6]}" = "            <tr><td align=\"left\" border=\"1\"><b>Borders</b>: USA</td></tr>" ]
    [ "${lines[7]}" = "        </table>>" ]
    [ "${lines[8]}" = "    ];" ]
    [ "${lines[9]}" = "}" ]
}

@test "Afficher format \"dot\" sur Canada avec --show-capital --show-languages --show-borders" {
    run ../bin/run --country can --output-format dot --show-capital --show-languages --show-borders
    [ "${lines[0]}" = "graph {" ]
    [ "${lines[1]}" = "    can [" ]
    [ "${lines[2]}" = "        shape = none," ]
    [ "${lines[3]}" = "        label = <<table border=\"0\" cellspacing=\"0\">" ]
    [ "${lines[4]}" = "            <tr><td align=\"left\" border=\"1\"><b>Name</b>: Canada</td></tr>" ]
    [ "${lines[5]}" = "            <tr><td align=\"left\" border=\"1\"><b>Code</b>: CAN</td></tr>" ]
    [ "${lines[6]}" = "            <tr><td align=\"left\" border=\"1\"><b>Capital</b>: Ottawa</td></tr>" ]
    [ "${lines[7]}" = "            <tr><td align=\"left\" border=\"1\"><b>Languages</b>: English, French</td></tr>" ]
    [ "${lines[8]}" = "            <tr><td align=\"left\" border=\"1\"><b>Borders</b>: USA</td></tr>" ]
    [ "${lines[9]}" = "        </table>>" ]
    [ "${lines[10]}" = "    ];" ]
    [ "${lines[11]}" = "}" ]
}

@test "Afficher format \"dot\" du premier pays du fichier JSON (Aruba)" {
    run ../bin/run --country abw --output-format dot --show-capital --show-languages --show-borders
    [ "${lines[0]}" = "graph {" ]
    [ "${lines[1]}" = "    abw [" ]
    [ "${lines[2]}" = "        shape = none," ]
    [ "${lines[3]}" = "        label = <<table border=\"0\" cellspacing=\"0\">" ]
    [ "${lines[4]}" = "            <tr><td align=\"left\" border=\"1\"><b>Name</b>: Aruba</td></tr>" ]
    [ "${lines[5]}" = "            <tr><td align=\"left\" border=\"1\"><b>Code</b>: ABW</td></tr>" ]
    [ "${lines[6]}" = "            <tr><td align=\"left\" border=\"1\"><b>Capital</b>: Oranjestad</td></tr>" ]
    [ "${lines[7]}" = "            <tr><td align=\"left\" border=\"1\"><b>Languages</b>: Dutch, Papiamento</td></tr>" ]
    [ "${lines[8]}" = "            <tr><td align=\"left\" border=\"1\"><b>Borders</b>:</td></tr>" ]
    [ "${lines[9]}" = "        </table>>" ]
    [ "${lines[10]}" = "    ];" ]
    [ "${lines[11]}" = "}" ]
}

@test "Afficher format \"dot\" du dernier pays du fichier JSON (Zimbabwe)" {
    run ../bin/run --country zwe --output-format dot --show-capital --show-languages --show-borders
    [ "${lines[0]}" = "graph {" ]
    [ "${lines[1]}" = "    zwe [" ]
    [ "${lines[2]}" = "        shape = none," ]
    [ "${lines[3]}" = "        label = <<table border=\"0\" cellspacing=\"0\">" ]
    [ "${lines[4]}" = "            <tr><td align=\"left\" border=\"1\"><b>Name</b>: Zimbabwe</td></tr>" ]
    [ "${lines[5]}" = "            <tr><td align=\"left\" border=\"1\"><b>Code</b>: ZWE</td></tr>" ]
    [ "${lines[6]}" = "            <tr><td align=\"left\" border=\"1\"><b>Capital</b>: Harare</td></tr>" ]
    [ "${lines[7]}" = "            <tr><td align=\"left\" border=\"1\"><b>Languages</b>: Chewa, Chibarwe, English, Kalanga, Khoisan, Ndau, Northern Ndebele, Shona, Sotho, Tonga, Tsonga, Tswana, Venda, Xhosa, Zimbabwean Sign Language</td></tr>" ]
    [ "${lines[8]}" = "            <tr><td align=\"left\" border=\"1\"><b>Borders</b>: BWA MOZ ZAF ZMB</td></tr>" ]
    [ "${lines[9]}" = "        </table>>" ]
    [ "${lines[10]}" = "    ];" ]
    [ "${lines[11]}" = "}" ]
}

@test "La commande --country a priorite sur la commande --region" {
    run ../bin/run --country can --region-europe --output-format dot --show-capital --show-languages --show-borders
    [ "${lines[0]}" = "graph {" ]
    [ "${lines[1]}" = "    can [" ]
    [ "${lines[2]}" = "        shape = none," ]
    [ "${lines[3]}" = "        label = <<table border=\"0\" cellspacing=\"0\">" ]
    [ "${lines[4]}" = "            <tr><td align=\"left\" border=\"1\"><b>Name</b>: Canada</td></tr>" ]
    [ "${lines[5]}" = "            <tr><td align=\"left\" border=\"1\"><b>Code</b>: CAN</td></tr>" ]
    [ "${lines[6]}" = "            <tr><td align=\"left\" border=\"1\"><b>Capital</b>: Ottawa</td></tr>" ]
    [ "${lines[7]}" = "            <tr><td align=\"left\" border=\"1\"><b>Languages</b>: English, French</td></tr>" ]
    [ "${lines[8]}" = "            <tr><td align=\"left\" border=\"1\"><b>Borders</b>: USA</td></tr>" ]
    [ "${lines[9]}" = "        </table>>" ]
    [ "${lines[10]}" = "    ];" ]
    [ "${lines[11]}" = "}" ]
}
