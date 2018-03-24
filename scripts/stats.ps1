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

function Draw-ResultRow( $wins, $loose, $draw, $name )
{
    $relevantMatches = @($input)

    $isWin = $relevantMatches | where $wins | measure | % Count
    $isFairWin = $relevantMatches | where $wins | where{ $_.Fair -eq "true" } | measure | % Count
    $isLoose = $relevantMatches | where $loose | measure | % Count
    $isDraw = $relevantMatches | where $draw | measure | % Count
    $total = $isWin + $isLoose + $isDraw

    "    {0,2}/{1,-2}  {2,2}   {3,2}    {4,2}    $name" -f $isWin, $isFairWin, $isLoose, $isDraw, $total
}

function Show-PlayersStats( $history )
{
    ""
    Write-Host "Players" -fore DarkYellow
    Write-Host "   win/fair loose draw  total" -fore DarkCyan
    $players = $history.FirstPlayer + $history.SecondPlayer | sort -Unique

    foreach( $player in $players )
    {
        $relevantMatches = $history |
            where{ ($_.FirstPlayer -eq $player) -or ($_.SecondPlayer -eq $player) }

        $relevantMatches | Draw-ResultRow `
            {($_.Winner -eq $player)} `
            {($_.Winner -ne $player) -and ($_.Winner -ne "draw")} `
            {($_.Winner -eq "draw")} `
            $player
    }
}

function Show-FighterStats( $history )
{
    ""
    Write-Host "Fighters" -fore DarkYellow
    $games = $history | group Game

    foreach( $game in $games )
    {
        Write-Host " $($game.Name)" -fore DarkYellow
        Write-Host "   win/f loose draw  total" -fore DarkCyan
        $fighters = $game.Group.FirstFighter + $game.Group.SecondFighter | group | sort Count -desc

        foreach( $fighter in $fighters.Name )
        {
            $relevantMatches = $game.Group |
                where{ ($_.FirstFighter -eq $fighter) -or ($_.SecondFighter -eq $fighter) }

            $relevantMatches | Draw-ResultRow `
                {(($fighter -eq $_.FirstFighter)  -and ($_.Winner -eq $_.FirstPlayer)) -or
                 (($fighter -eq $_.SecondFighter) -and ($_.Winner -eq $_.SecondPlayer))} `
                {(($fighter -eq $_.FirstFighter) -and ($_.Winner -eq $_.SecondPlayer)) -or
                 (($fighter -eq $_.SecondFighter) -and ($_.Winner -eq $_.FirstPlayer))} `
                {(($fighter -eq $_.FirstFighter) -or (($fighter -eq $_.SecondFighter))) -and
                 (($_.Winner -eq "draw"))} `
                $fighter
        }
        ""
    }
}

function Show-PairsStats( $history, $players )
{
    ""
    Write-Host "Pairs" -fore DarkYellow
    Write-Host "   win1 win2 draw  total" -fore DarkCyan

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
    Write-Host "   win  fail draw  total" -fore DarkCyan

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

