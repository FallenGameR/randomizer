[Reflection.Assembly]::LoadWithPartialName("System.Windows.Forms")

$dataPath = Join-Path $PsScriptRoot "..\data"

function Convert-Bmp( $file )
{
    $path = if( $file -is [IO.FileInfo] ) { $file.FullName } else { $file }
    $convertFile = New-Object System.Drawing.Bitmap($path)
    $newFile = $convertFile.Clone(
        [System.Drawing.Rectangle]::FromLTRB(0, 0, $convertFile.Width, $convertFile.Height),
        [System.Drawing.Imaging.PixelFormat]::Format24bppRgb)
    $newFile.Save("$path.tmp", [System.Drawing.Imaging.ImageFormat]::Bmp)
    $newFile.Dispose()
    $convertFile.Dispose()
    Remove-Item $path
    Rename-Item "$path.tmp" $path
}

$files = ls $dataPath -Recurse -Include *.bmp
$files = ls data\games\*\icon.bmp
foreach( $iconFile in $files )
{
    Convert-Bmp $iconFile
}