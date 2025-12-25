$files = Get-ChildItem *.bmp | Sort-Object { $_.Name.Length }, { $_.Name }
foreach ($file in $files) {
    if ($file.Name -match "^(.*[^0-9])?([0-9]+)(\.bmp)$") {
        $newName = $matches[1] + ("{0:D" + $matches[2].Length + "}" -f ([int]$matches[2] - 1)) + $matches[3]
        Rename-Item -LiteralPath $file.FullName -NewName $newName
    }
}