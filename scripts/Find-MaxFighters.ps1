$dataPath = Join-Path $PsScriptRoot "..\data"

$fighters = foreach( $game in ls $dataPath\games )
{
    ls $game\fighters | m | % count
}

# 54
$fighters | m -Maximum | % Maximum