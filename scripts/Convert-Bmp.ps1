[Reflection.Assembly]::LoadWithPartialName("System.Windows.Forms")

$dataPath = Join-Path $PsScriptRoot "..\data"

function Convert-Bmp( $file )
{
    $path = if( $file -is [IO.FileInfo] ) { $path.FullName } else { $file }
    $convertFile = New-Object System.Drawing.Bitmap($path)
    $newFile = $convertFile.Clone(
        [System.Drawing.Rectangle]::FromLTRB(0, 0, $convertFile.Width, $convertFile.Height),
        [System.Drawing.Imaging.PixelFormat]::Format24bppRgb)
    $newFile.Save("$iconFile.tmp", [System.Drawing.Imaging.ImageFormat]::Bmp)
    $newFile.Dispose()
    $convertFile.Dispose()
    Remove-Item $iconFile
    Rename-Item "$iconFile.tmp" "$iconFile"
}

foreach( $iconFile in ls $dataPath -Recurse -Include *.bmp )
{
    Convert-Bmp $iconFile
}