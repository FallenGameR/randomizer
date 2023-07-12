$dataPath = Join-Path $PsScriptRoot "..\data\"

# Max length of a path part is 8
$maxPathPartViolations = ls $dataPath\games -Recurse | % Name | where Length -gt 8
if( $maxPathPartViolations )
{
    Write-Error "The following path parts are too long, they need to be max 8 chars to satisfy BUFFER_PATH_MAX_LENGTH: $maxPathPartViolations"
}

# Every game has a proper name
foreach( $game in ls $dataPath\games -Directory )
{
    $nameFile = Join-Path $game name.txt

    if( -not (Test-Path $nameFile) )
    {
        Write-Error "Missing name.txt for game $game"
        continue
    }

    $nameContent = @(Get-Content $nameFile)

    if( $nameContent.Length -ne 1 )
    {
        Write-Error "name.txt for game $($game.Name) should have exactly one line, but has $($nameContent.Length)"
        continue
    }

    if( $nameContent[0].Length -le 3 )
    {
        Write-Error "name.txt for game $($game.Name) is very short, it is just: $($nameContent[0])"
        continue
    }
}

# Every folder has name.txt that is not empty (and ends with EOL - although not sure it matters)
$folders = ls $dataPath\games
$names = ls $dataPath\games -Recurse | % Name | where { $_ -eq $null }