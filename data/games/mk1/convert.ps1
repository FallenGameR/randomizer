cd "C:\Users\alexk\Downloads\MK1"
$root = "D:\OneDrive\Projects\Hardware\Randomizer\data\games\mk1\Fighters"

$files = foreach( $file in ls ){
    [PSCustomObject] [ordered] @{
        Name = $file.BaseName
        DestinationFolderPath = Join-Path $root ($file.BaseName -replace ' ')
        SourceFilePath = $file.FullName
    }
}

$files | foreach{ mkdir $PSItem.DestinationFolderPath}
$files | foreach{ Copy-Item $PSItem.SourceFilePath "$($PSItem.DestinationFolderPath)\icon.png" }
$files | foreach{ $PSItem.Name > "$($PSItem.DestinationFolderPath)\name.txt" }
```
