<#
How often player wins with a character?
How often there is a fair play for a player?
Are characters evenly distributed?
#>

function Get-MatchResults( $info, $condition, $oposite )
{
    $relevantMatches = @($input)

    $isTrue = $relevantMatches | where $condition | measure | % Count
    $isFalse = $relevantMatches | where $oposite | measure | % Count
    $isDraw = $relevantMatches | where Winner -eq "draw" | measure | % Count

    "    {0,2} | {1,2} | {2,2}    {3,2}   $info" -f $isTrue, $isFalse, $isDraw, ($isTrue + $isFalse + $isDraw)
}

function Show-PlayersStats( $history, $players )
{
    ""
    Write-Host "Players" -fore DarkYellow

    foreach( $player in $players )
    {
        $relevantMatches = $history | where{ ($_.FirstPlayer -eq $player) -or ($_.SecondPlayer -eq $player) }
        $relevantMatches | Get-MatchResults `
            $player `
            {$_.Winner -eq $player} `
            {($_.Winner -ne $player) -and ($_.Winner -ne "draw")}
    }
}

function Show-FighterStats( $history )
{
    ""
    Write-Host "Fighters" -fore DarkYellow
    $fighters = $history.FirstFighter + $history.SecondFighter | sort -Unique

    foreach( $fighter in $fighters )
    {
        $relevantMatches = $history | where{ ($_.FirstFighter -eq $fighter) -or ($_.SecondFighter -eq $fighter) }
        $relevantMatches | Get-MatchResults `
            $fighter `
            {(($fighter -eq $_.FirstFighter) -and ($_.Winner -eq $_.FirstPlayer)) -or (($fighter -eq $_.SecondFighter) -and ($_.Winner -eq $_.SecondPlayer))} `
            {(($fighter -eq $_.FirstFighter) -and ($_.Winner -eq $_.SecondPlayer)) -or (($fighter -eq $_.SecondFighter) -and ($_.Winner -eq $_.FirstPlayer))}
    }
}

function Show-PairsStats( $history, $players )
{
    ""
    Write-Host "Pairs" -fore DarkYellow

    $set = $players
    foreach( $player in $players )
    {
        $set = $set | where{ $psitem -ne $player }
        foreach( $partner in $set )
        {
            $relevantMatches = @($history | where{
                (($_.FirstPlayer -eq $player) -or ($_.SecondPlayer -eq $player)) -and
                (($_.FirstPlayer -eq $partner) -or ($_.SecondPlayer -eq $partner)) })
            $relevantMatches | Get-MatchResults "$player vs $partner" {$_.Winner -eq $player} {$_.Winner -eq $partner}
        }
    }
}

function Show-ChairsStats( $history, $players )
{
    ""
    Write-Host "Chairs" -fore DarkYellow

    $history | Get-MatchResults "First chair" {$_.Winner -eq $_.FirstPlayer} {$_.Winner -eq $_.SecondPlayer}
    foreach( $player in $players )
    {
        $relevantMatches = $history | where{ $_.FirstPlayer -eq $player }
        $info = $relevantMatches | Get-MatchResults `
            $player `
            {$_.Winner -eq $player} `
            {($_.Winner -ne $player) -and ($_.Winner -ne "draw")}
        " $info"
    }
    ""

    $history | Get-MatchResults "Second chair" {$_.Winner -eq $_.SecondPlayer} {$_.Winner -eq $_.FirstPlayer}
    foreach( $player in $players )
    {
        $relevantMatches = $history | where{ $_.SecondPlayer -eq $player }
        $info = $relevantMatches | Get-MatchResults `
            $player `
            {$_.Winner -eq $player} `
            {($_.Winner -ne $player) -and ($_.Winner -ne "draw")}
        " $info"
    }
    ""
}

function Show-Stats( $path = "f:\OneDrive\Projects\Hobbies\Hardware\randomizer\data\sample.csv" )
{
    $history = Import-Csv $path
    $players = $history.FirstPlayer + $history.SecondPlayer | sort -Unique

    Show-PlayersStats $history $players
    Show-FighterStats $history
    Show-PairsStats $history $players
    Show-ChairsStats $history $players
}

