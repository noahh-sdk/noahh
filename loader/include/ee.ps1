# replace.ps1
param(
    [string]$Root = "."
)

# Extensions to skip when editing file contents
$skip = @(".dll", ".exe", ".obj", ".bin", ".pdb")

# Full path of this script
$Self = $MyInvocation.MyCommand.Path
$SelfName = Split-Path $Self -Leaf

function Replace-Name($text) {
    $text = $text -creplace 'Geode', 'Noahh'
    $text = $text -creplace 'geode', 'noahh'
    $text = $text -creplace 'GEODE', 'NOAHH'
    return $text
}

Write-Host "=== Renaming folders ==="

# Rename directories deepest-first
Get-ChildItem -Path $Root -Recurse -Directory |
    Sort-Object FullName -Descending |
    ForEach-Object {
        $oldPath = $_.FullName
        $oldName = $_.Name
        $newName = Replace-Name $oldName

        # Skip if name doesn't change
        if ($oldName -eq $newName) { return }

        Write-Host "Renamed folder: $oldPath -> $newName"
        Rename-Item -LiteralPath $oldPath -NewName $newName
    }

Write-Host "=== Renaming files ==="

Get-ChildItem -Path $Root -Recurse -File | ForEach-Object {
    # Skip the script itself
    if ($_.FullName -eq $Self) { return }

    $oldPath = $_.FullName
    $oldName = $_.Name
    $newName = Replace-Name $oldName

    if ($oldName -ne $newName) {
        Write-Host "Renamed file: $oldPath -> $newName"
        Rename-Item -LiteralPath $oldPath -NewName $newName
    }
}

Write-Host "=== Editing file contents ==="

Get-ChildItem -Path $Root -Recurse -File | ForEach-Object {
    # Skip binaries
    if ($skip -contains $_.Extension.ToLower()) { return }

    # Skip the script itself
    if ($_.FullName -eq $Self) { return }

    $content = Get-Content $_.FullName -Raw
    $original = $content

    $content = Replace-Name $content

    if ($content -ne $original) {
        Write-Host "Edited contents: $($_.FullName)"
        Set-Content -Path $_.FullName -Value $content
    }
}

Write-Host "=== Done ==="
