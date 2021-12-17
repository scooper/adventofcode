package main

import (
	utilities "adventofcode/utility/common"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"math"
	"os"
	"strings"
)

type coord struct {
	x, y float64
}

type line struct {
	start, end coord
	diagonal   bool
}

func compareVentGrids(grid1 [][]int, grid2 [][]int, max coord) [][]int {
	diffGrid := createEmptyVentGrid(max)

	maxX := int(max.x)
	maxY := int(max.y)

	for y := 0; y < maxY; y++ {
		for x := 0; x < maxX; x++ {
			if grid1[y][x] != grid2[y][x] {
				diffGrid[y][x] += 2
			}
		}
	}

	return diffGrid
}

func interpolate(v0 float64, v1 float64, t float64) float64 {
	return (1.0-t)*v0 + t*v1
}

func createEmptyVentGrid(max coord) [][]int {
	// creat vents array
	var vents [][]int
	limitY := int(max.y)
	limitX := int(max.x)
	vents = make([][]int, limitY)
	for y := 0; y < limitY; y++ {
		vents[y] = make([]int, limitX)
	}

	return vents
}

func calculateVentLoationsNaive(ventLines []line, max coord, includeDiagonal bool) [][]int {
	vents := createEmptyVentGrid(max)

	for _, ventLine := range ventLines {

		if ventLine.diagonal && !includeDiagonal {
			continue
		}

		var yIncrement int
		if ventLine.start.y < ventLine.end.y {
			yIncrement = 1
		} else if ventLine.start.y > ventLine.end.y {
			yIncrement = -1
		} else {
			yIncrement = 0
		}

		var xIncrement int
		if ventLine.start.x < ventLine.end.x {
			xIncrement = 1
		} else if ventLine.start.x > ventLine.end.x {
			xIncrement = -1
		} else {
			xIncrement = 0
		}

		x := ventLine.start.x
		y := ventLine.start.y

		for x != ventLine.end.x+float64(xIncrement) || y != ventLine.end.y+float64(yIncrement) {
			vents[int(y)][int(x)] += 1
			x += float64(xIncrement)
			y += float64(yIncrement)
		}

	}

	return vents
}

// too inaccurate - needs work
func calculateVentLocations(ventLines []line, max coord, includeDiagonal bool) [][]int {

	vents := createEmptyVentGrid(max)

	for _, ventLine := range ventLines {
		// skip diagonal
		if ventLine.diagonal && !includeDiagonal {
			continue
		}

		// all the diagonals are 45 degrees so these will always be the same
		diffx := ventLine.end.x - ventLine.start.x
		diffy := ventLine.end.y - ventLine.start.y
		lineLength := math.Hypot(diffx, diffy)

		stepSize := 1.0 / lineLength

		cache := make(map[string]int)

		for step := 0.0; step <= lineLength; step++ {
			t := stepSize * step
			x := int(math.Round(interpolate(ventLine.start.x, ventLine.end.x, t)))
			y := int(math.Round(interpolate(ventLine.start.y, ventLine.end.y, t)))

			key := fmt.Sprintf("%d-%d", x, y)

			// avoid duplicates
			if _, found := cache[key]; found {
				continue
			} else {
				cache[key] += 1
				vents[y][x] += 1

			}
		}
	}

	return vents
}

func writeVentsToFileAndReturnIntersections(vents [][]int, max coord, filename string) int {
	file, err := os.Create(fmt.Sprintf("%s.png", filename))

	utilities.CheckError(err)

	defer file.Close()

	maxX := int(max.x)
	maxY := int(max.y)
	image := image.NewRGBA(image.Rect(0, 0, maxX, maxY))

	intersections := 0
	for y := 0; y < maxY; y++ {
		for x := 0; x < maxX; x++ {
			var colorWeighted uint8
			if vents[y][x] >= 2 {
				colorWeighted = 255
				intersections++
			} else if vents[y][x] > 0 {
				colorWeighted = 50
			} else {
				colorWeighted = 0
			}
			col := color.RGBA{colorWeighted, colorWeighted, colorWeighted, 255}
			image.Set(x, y, col)
		}
	}

	png.Encode(file, image)

	return intersections
}

func main() {
	input, readErr := utilities.ReadFileIntoSliceSplitString("input", " -> ")

	utilities.CheckError(readErr)

	var ventLines []line

	// popuate lines

	max := coord{x: 0, y: 0}
	for _, inputLine := range input {
		startCoords := utilities.StringSliceToIntSlice(strings.Split(inputLine[0], ","))
		endCoords := utilities.StringSliceToIntSlice(strings.Split(inputLine[1], ","))

		var lineElement line
		lineElement.start.x = float64(startCoords[0])
		lineElement.start.y = float64(startCoords[1])
		lineElement.end.x = float64(endCoords[0])
		lineElement.end.y = float64(endCoords[1])

		if !(lineElement.start.x == lineElement.end.x || lineElement.start.y == lineElement.end.y) {
			lineElement.diagonal = true
		}

		max.x = math.Max(math.Max(lineElement.start.x, lineElement.end.x), max.x)
		max.y = math.Max(math.Max(lineElement.start.y, lineElement.end.y), max.y)
		ventLines = append(ventLines, lineElement)
	}

	max.x += 1
	max.y += 1

	vents1 := calculateVentLoationsNaive(ventLines, max, false)
	vents2 := calculateVentLocations(ventLines, max, false)
	vents3 := calculateVentLoationsNaive(ventLines, max, true)
	vents4 := calculateVentLocations(ventLines, max, true)

	intersections1 := writeVentsToFileAndReturnIntersections(vents1, max, "vents-no-diagonal(naive)")
	intersections2 := writeVentsToFileAndReturnIntersections(vents2, max, "vents-no-diagonal(interpolation)")

	fmt.Printf("Intersections for non-diagonals(naive): %d\n", intersections1)
	fmt.Printf("Intersections for non-diagonals(interpolation): %d\n", intersections2)

	intersections3 := writeVentsToFileAndReturnIntersections(vents3, max, "vents-diagonals(naive)")
	intersections4 := writeVentsToFileAndReturnIntersections(vents4, max, "vents-diagonals(interpolation)")

	fmt.Printf("Intersections including diagonals(naive): %d\n", intersections3)
	fmt.Printf("Intersections including diagonals(interpolation): %d\n", intersections4)
}
