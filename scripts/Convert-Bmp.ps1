[Reflection.Assembly]::LoadWithPartialName("System.Windows.Forms")

$dataPath = Join-Path $PsScriptRoot "..\data"
$icons = ls $dataPath -Recurse -Include *.bmp

foreach( $icon in $icons )
{
    $convertFile = New-Object System.Drawing.Bitmap($iconFile)
    $newFile = $convertFile.Clone(
        [System.Drawing.Rectangle]::FromLTRB(0, 0, $convertFile.Width, $convertFile.Height),
        [System.Drawing.Imaging.PixelFormat]::Format24bppRgb)
    $newFile.Save("$iconFile.tmp", [System.Drawing.Imaging.ImageFormat]::Bmp)
    $newFile.Dispose()
    $convertFile.Dispose()
    Remove-Item $iconFile
    Rename-Item "$iconFile.tmp" "$iconFile" -Verbose
}