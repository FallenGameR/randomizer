<#
How often player wins with a character?
#>

function Draw-WinWinRow( $wins1, $wins2, $draw, $name )
{
    $relevantMatches = @($input)

    $isWin1 = $relevantMatches | where $wins1 | measure | % Count
    $isFairWin1 = $relevantMatches | where $wins1 | where{ $_.Fair -eq "true" } | measure | % Count

    $isWin2 = $relevantMatches | where $wins2 | measure | % Count
    $isFairWin2 = $relevantMatches | where $wins2 | where{ $_.Fair -eq "true" } | measure | % Count

    $isDraw = $relevantMatches | where $draw | measure | % Count
    $total = $isWin1 + $isWin2 + $isDraw

    Write-Host "   "  -NoNewline
    Write-Host ("{0,2}" -f $isWin1) -fore Gray -NoNewline
    Write-Host (" {0,-2}" -f $isFairWin1) -fore DarkGray -NoNewline

    Write-Host "   "  -NoNewline
    Write-Host ("{0,2}" -f $isWin2) -fore Gray -NoNewline
    Write-Host (" {0,-2}" -f $isFairWin2) -fore DarkGray -NoNewline

    Write-Host "   "  -NoNewline
    Write-Host ("{0,2}" -f $isDraw) -fore Gray -NoNewline

    Write-Host "     "  -NoNewline
    Write-Host ("{0,2}" -f $total) -fore Gray -NoNewline

    Write-Host "    "  -NoNewline
    Write-Host ("{0}" -f $name) -fore Gray
}

function Draw-ResultRow( $wins, $loose, $draw, $name )
{
    $relevantMatches = @($input)

    $isWin = $relevantMatches | where $wins | measure | % Count
    $isWinFair = $relevantMatches | where $wins | where{ $_.Fair -eq "true" } | measure | % Count

    $isLoose = $relevantMatches | where $loose | measure | % Count
    $isLooseFair = $relevantMatches | where $loose | where{ $_.Fair -eq "true" } | measure | % Count

    $isDraw = $relevantMatches | where $draw | measure | % Count
    $total = $isWin + $isLoose + $isDraw

    Write-Host "    "  -NoNewline
    Write-Host ("{0,2}" -f $isWin) -fore Gray -NoNewline
    Write-Host (" {0,-2}" -f $isWinFair) -fore DarkGray -NoNewline

    Write-Host "   "  -NoNewline
    Write-Host ("{0,2}" -f $isLoose) -fore Gray -NoNewline
    Write-Host (" {0,-2}" -f $isLooseFair) -fore DarkGray -NoNewline

    Write-Host "   "  -NoNewline
    Write-Host ("{0,2}" -f $isDraw) -fore Gray -NoNewline

    Write-Host "     "  -NoNewline
    Write-Host ("{0,2}" -f $total) -fore Gray -NoNewline

    Write-Host "    "  -NoNewline
    Write-Host ("{0}" -f $name) -fore Gray
}

function Show-PairsStats( $history )
{
    ""
    Write-Host "Pairs" -fore DarkYellow
    Write-Host "  win1/f  win2/f  draw  total" -fore DarkCyan
    $players = $history.FirstPlayer + $history.SecondPlayer | sort -Unique

    $set = $players
    foreach( $player in $players )
    {
        $set = $set | where{ $psitem -ne $player }
        foreach( $partner in $set )
        {
            $relevantMatches = @($history | where{
                (($_.FirstPlayer -eq $player) -or ($_.SecondPlayer -eq $player)) -and
                (($_.FirstPlayer -eq $partner) -or ($_.SecondPlayer -eq $partner)) })

            $relevantMatches | Draw-WinWinRow `
                {$_.Winner -eq $player} `
                {$_.Winner -eq $partner} `
                {$_.Winner -eq "draw"} `
                "$player vs $partner"
        }
    }
}

function Show-PlayersStats( $history )
{
    ""
    Write-Host "Players" -fore DarkYellow
    Write-Host "    win/f  lost/f  draw  total" -fore DarkCyan
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

function Show-FighterPerPlayerStats( $history )
{
    ""
    Write-Host "Fighters" -fore DarkYellow
    $games = $history | group Game

    foreach( $game in $games )
    {
        Write-Host " $($game.Name)" -fore DarkYellow
        $players = $game.Group.FirstPlayer + $game.Group.SecondPlayer | sort -Unique

        foreach( $player in $players )
        {
            Write-Host "  $player" -fore DarkYellow
            Write-Host "    win/f  lost/f  draw  total" -fore DarkCyan

            $fighters = $game.Group | foreach{
                if( ($_.FirstPlayer -eq $player) ) {$_.FirstFighter}
                if( ($_.SecondPlayer -eq $player) ) {$_.SecondFighter} } |
                group | sort Count -desc

            foreach( $fighter in $fighters.Name )
            {
                $relevantMatches = $game.Group | where{
                    (($_.FirstPlayer -eq $player) -and ($_.FirstFighter -eq $fighter)) -or
                    (($_.SecondPlayer -eq $player) -and ($_.SecondFighter -eq $fighter)) }

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

    Show-PairsStats $history
    Show-PlayersStats $history
    Show-FighterStats $history
    Show-ChairsStats $history
}

