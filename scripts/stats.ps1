function Draw-WinWinRow( $wins1, $wins2, $draw, $name )
{
    $relevantMatches = @($input)

    $isWin1 = $relevantMatches | where $wins1 | measure | % Count
    $isWin1Unfair = $relevantMatches | where $wins1 | where{ $_.Fair -ne "true" } | measure | % Count

    $isWin2 = $relevantMatches | where $wins2 | measure | % Count
    $isWin2Unfair = $relevantMatches | where $wins2 | where{ $_.Fair -ne "true" } | measure | % Count

    $isDraw = $relevantMatches | where $draw | measure | % Count
    $total = $isWin1 + $isWin2 + $isDraw

    if( -not $total )
    {
        return
    }

    Write-Host "    "  -NoNewline
    if( $isWin1Unfair )
    {
        Write-Host ("{0,2}" -f $isWin1) -fore Gray -NoNewline
        Write-Host ("-{0,-2}" -f $isWin1Unfair) -fore DarkGreen -NoNewline
    }
    else
    {
        Write-Host ("{0,2}" -f $isWin1) -fore Gray -NoNewline
        Write-Host "   " -NoNewline
    }

    Write-Host "   "  -NoNewline
    if( $isWin2Unfair )
    {
        Write-Host ("{0,2}" -f $isWin2) -fore Gray -NoNewline
        Write-Host ("-{0,-2}" -f $isWin2Unfair) -fore DarkGreen -NoNewline
    }
    else
    {
        Write-Host ("{0,2}" -f $isWin2) -fore Gray -NoNewline
        Write-Host "   " -NoNewline
    }

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
    $isWinUnfair = $relevantMatches | where $wins | where{ $_.Fair -ne "true" } | measure | % Count

    $isLoose = $relevantMatches | where $loose | measure | % Count
    $isLooseUnfair = $relevantMatches | where $loose | where{ $_.Fair -ne "true" } | measure | % Count

    $isDraw = $relevantMatches | where $draw | measure | % Count
    $total = $isWin + $isLoose + $isDraw

    if( -not $total )
    {
        return
    }

    Write-Host "    "  -NoNewline
    if( $isWinUnfair )
    {
        Write-Host ("{0,2}" -f $isWin) -fore Gray -NoNewline
        Write-Host ("-{0,-2}" -f $isWinUnfair) -fore DarkGreen -NoNewline
    }
    else
    {
        Write-Host ("{0,2}" -f $isWin) -fore Gray -NoNewline
        Write-Host "   " -NoNewline
    }

    Write-Host "   "  -NoNewline
    if( $isLooseUnfair )
    {
        Write-Host ("{0,2}" -f $isLoose) -fore Gray -NoNewline
        Write-Host ("-{0,-2}" -f $isLooseUnfair) -fore DarkGreen -NoNewline
    }
    else
    {
        Write-Host ("{0,2}" -f $isLoose) -fore Gray -NoNewline
        Write-Host "   " -NoNewline
    }

    Write-Host "   "  -NoNewline
    if( $isDraw )
    {
        Write-Host ("{0,2}" -f $isDraw) -fore Gray -NoNewline
    }
    else
    {
        Write-Host "  " -NoNewline
    }

    Write-Host "     "  -NoNewline
    Write-Host ("{0,2}" -f $total) -fore Gray -NoNewline

    Write-Host "    "  -NoNewline
    Write-Host ("{0}" -f $name) -fore Gray
}

function Show-PairsStats( $history )
{
    ""
    Write-Host "Pairs" -fore DarkYellow
    Write-Host "    win1    win2   draw  total" -fore DarkCyan

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
    Write-Host "     win    lost   draw  total" -fore DarkCyan
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

    # Figher per player stats
    $players = $history.FirstPlayer + $history.SecondPlayer | sort -Unique

    foreach( $player in $players )
    {
        Write-Host "  $player" -fore DarkYellow
        Write-Host "     win    lost   draw  total" -fore DarkCyan

        $fightersRaw = foreach( $item in $history )
        {
            if( $item.FirstPlayer -eq $player )
            {
                $item.FirstFighter
                $item.FirstFighter2
                $item.FirstFighter3
            }
            if( $item.SecondPlayer -eq $player )
            {
                $item.SecondFighter
                $item.SecondFighter2
                $item.SecondFighter3
            }
        }
        $fighters = $fightersRaw | where{ $_ } | group | sort Count -desc

        foreach( $fighter in $fighters.Name )
        {
            $relevantMatches = $history | where{
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

function Show-ChairsStats( $history )
{
    ""
    Write-Host "Chairs" -fore DarkYellow
    Write-Host "     win    lost   draw  total" -fore DarkCyan
    $players = $history.FirstPlayer + $history.SecondPlayer | sort -Unique

    $history | Draw-ResultRow `
        {$_.Winner -eq $_.FirstPlayer} `
        {$_.Winner -eq $_.SecondPlayer} `
        {$_.Winner -eq "draw"} `
        "First chair"

    foreach( $player in $players )
    {
        $relevantMatches = $history | where{ $_.FirstPlayer -eq $player }
        $relevantMatches | Draw-ResultRow `
            {($_.Winner -eq $player)} `
            {($_.Winner -ne $player) -and ($_.Winner -ne "draw")} `
            {($_.Winner -eq "draw")} `
            "  $player" `
    }
    ""

    $history | Draw-ResultRow `
        {$_.Winner -eq $_.SecondPlayer} `
        {$_.Winner -eq $_.FirstPlayer} `
        {$_.Winner -eq "draw"} `
        "Second chair"

    foreach( $player in $players )
    {
        $relevantMatches = $history | where{ $_.SecondPlayer -eq $player }
        $relevantMatches | Draw-ResultRow `
            {($_.Winner -eq $player)} `
            {($_.Winner -ne $player) -and ($_.Winner -ne "draw")} `
            {($_.Winner -eq "draw")} `
            "  $player" `
    }
}

function Show-Stats( $path = "f:\OneDrive\Projects\Hobbies\Hardware\randomizer\data\tag_sample.csv" )
{
    function Show-Output( $name, $scope )
    {
        $players = @($scope.FirstPlayer + $scope.SecondPlayer | sort -Unique)

        cls
        Write-Host $name -fore Green

        Show-PairsStats $scope
        if( $players.Length -gt 2 )
        {
            Show-PlayersStats $scope
            Show-ChairsStats $scope
        }
        Show-FighterStats $scope
        Read-Host
    }

    $history = Import-Csv $path
    Show-Output "Totals" $history

    $games = $history | group Game
    foreach( $game in $games )
    {
        Show-Output $game.Name $game.Group
    }
}

