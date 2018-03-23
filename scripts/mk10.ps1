function Get-RandomPlayers( $players, $history )
{
    # Players are taken in a way that there is no unfair wait

    # Sort by the least played count
    $raw = foreach( $player in $players )
    {
        $playedIn = @($history | where{ ($_.First -eq $player) -or ($_.Second -eq $player) })
        [PsCustomObject] [ordered] @{
            Player = $player
            Matches = $playedIn.Length
        }
    }
    $stat = $raw | group Matches | sort {[int]$_.Name}

    # Get the player pool - first one or two groups
    # of players who played less then others
    $mandatory = $null
    $pool = @($stat | select -first 1 | foreach{ $psitem.Group.Player })
    if( $pool.Length -eq 1 )
    {
        $mandatory = $pool
        $pool = @($stat | select -first 2 | foreach{ $psitem.Group.Player })
    }

    # Randomly pick the players from the pool
    do
    {
        $first = $pool | Get-Random
        $second = $pool | Get-Random
    }
    while( ($first -eq $second) -or ($mandatory -and ($mandatory -notin @($first, $second))) )

    # Return found players
    $first, $second
}

$GLOBAL:randomCalled = 0
$GLOBAL:router = @()

function New-Random( [string[]] $players, $roundsFair = 20 )
{
    if( $GLOBAL:randomCalled -eq $GLOBAL:router.Count )
    {
        $GLOBAL:router = @()
    }

    if( $GLOBAL:router.Count -eq 0 )
    {
        $pairs = for( $i = 0; $i -lt $players.Count - 1; $i += 1 )
        {
            for( $j = $i + 1; $j -lt $players.Count; $j += 1 )
            {
                [PsCustomObject] [ordered] @{
                    First = $players[$i]
                    Second = $players[$j]
                }
            }
        }

        $times = [Math]::Round($roundsFair / $pairs.Count)
        1..$times | foreach{ $pairs | foreach{ $GLOBAL:router += $psitem } }
        $GLOBAL:router = $GLOBAL:router | sort {Get-Random}
    }

    $index = $GLOBAL:randomCalled % $GLOBAL:router.Count
    $selected = $GLOBAL:router[$index]
    $GLOBAL:randomCalled += 1

    $selected.First, $selected.Second | sort {Get-Random}
}

function play( [string[]] $players )
{
    $matchHistory = @()

    do
    {
        $first, $second = New-Random $players # Get-RandomPlayers $players $matchHistory
        Write-Host "Match # $($matchHistory.Length + 1): $first VS $second" -fore DarkYellow

        do
        {
            $choise = Read-Host "Winner (1, 2, draw, exit)"
        }
        while( $choise -notmatch "^(1|2|draw|exit)$" )

        $record = [PsCustomObject] [ordered] @{
            First = $first
            Second = $second
            Winner = $null
        }
        switch ($choise)
        {
            "1" { $record.Winner = $first; $matchHistory += $record }
            "2" { $record.Winner = $second; $matchHistory += $record }
            "draw" { $record.Winner = "Draw"; $matchHistory += $record }
            "exit" {"exit"}
            default {"Wrong input: $psitem"}
        }
    }
    while( $choise -ne "exit" )

    $matchHistory
}

function Get-MatchResults( $info, $condition, $oposite )
{
    $relevantMatches = @($input)

    $isTrue = $relevantMatches | where $condition | measure | % Count
    $isFalse = $relevantMatches | where $oposite | measure | % Count
    $isDraw = $relevantMatches | where Winner -eq "draw" | measure | % Count

    "    {0,2} | {1,2} | {2,2}   <{3,2}>  $info" -f $isTrue, $isFalse, $isDraw, $relevantMatches.Count
}

function analyse( $history, $players )
{
    ""
    Write-Host "Players" -fore DarkYellow

    foreach( $player in $players )
    {
        $relevantMatches = $history | where{ ($_.First -eq $player) -or ($_.Second -eq $player) }
        $relevantMatches | Get-MatchResults `
            $player `
            {$_.Winner -eq $player} `
            {($_.Winner -ne $player) -and ($_.Winner -ne "draw")}
    }

    ""
    Write-Host "Pairs" -fore DarkYellow

    $set = $players
    foreach( $player in $players )
    {
        $set = $set | where{ $psitem -ne $player }
        foreach( $partner in $set )
        {
            $relevantMatches = @($history | where{
                (($_.First -eq $player) -or ($_.Second -eq $player)) -and
                (($_.First -eq $partner) -or ($_.Second -eq $partner)) })
            $relevantMatches | Get-MatchResults "$player vs $partner" {$_.Winner -eq $player} {$_.Winner -eq $partner}
        }
    }

    ""
    Write-Host "Chairs" -fore DarkYellow

    $history | Get-MatchResults "First chair" {$_.Winner -eq $_.First} {$_.Winner -eq $_.Second}
    foreach( $player in $players )
    {
        $relevantMatches = $history | where{ $_.First -eq $player }
        $info = $relevantMatches | Get-MatchResults `
            $player `
            {$_.Winner -eq $player} `
            {($_.Winner -ne $player) -and ($_.Winner -ne "draw")}
        " $info"
    }
    ""

    $history | Get-MatchResults "Second chair" {$_.Winner -eq $_.Second} {$_.Winner -eq $_.First}
    foreach( $player in $players )
    {
        $relevantMatches = $history | where{ $_.Second -eq $player }
        $info = $relevantMatches | Get-MatchResults `
            $player `
            {$_.Winner -eq $player} `
            {($_.Winner -ne $player) -and ($_.Winner -ne "draw")}
        " $info"
    }
    ""
}

cls
$GLOBAL:players = "FallenGameR", "Pobeditel", "Vera"
$GLOBAL:history = play $players
analyse $history $players

