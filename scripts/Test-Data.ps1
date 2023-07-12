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
    $iconFile = Join-Path $game icon.bmp

    if( -not (Test-Path $iconFile) )
    {
        Write-Error "Missing icon.bmp for game $($game.Name)"
        continue
    }

    $nameFile = Join-Path $game name.txt

    if( -not (Test-Path $nameFile) )
    {
        Write-Error "Missing name.txt for game $($game.Name)"
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

# Every fighter has a proper name and icon
foreach( $fighter in ls $dataPath\games\*\Fighters\* -Directory )
{
    $iconFile = Join-Path $fighter icon.bmp

    if( -not (Test-Path $iconFile) )
    {
        Write-Error "Missing icon.bmp for fighter $($fighter.Name)"
        continue
    }

    $nameFile = Join-Path $fighter name.txt

    if( -not (Test-Path $nameFile) )
    {
        Write-Error "Missing name.txt for fighter $($fighter.Name)"
        continue
    }

    $nameContent = @(Get-Content $nameFile)

    if( $nameContent.Length -ne 1 )
    {
        Write-Error "name.txt for fighter $($fighter.Name) should have exactly one line, but has $($nameContent.Length)"
        continue
    }

    if( $nameContent[0].Length -le 1 )
    {
        Write-Error "name.txt for fighter $($fighter.Name) is very short, it is just: $($nameContent[0])"
        continue
    }
}
