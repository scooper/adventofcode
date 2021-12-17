package main

import (
	utilities "adventofcode/utility/common"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"os"
	"sort"
)

type positionFrequency struct {
	posData positionData
	count   int
}

type positionData struct {
	pos coordinate
	val int
}

type coordinate struct {
	x, y int
}

func coordinateToKey(coord coordinate) string {
	return fmt.Sprintf("%d-%d", coord.x, coord.y)
}

func neighbourFlowsUpCondition(original, neighbour int) bool {
	return (neighbour > original) && neighbour < 9
}

// returns all neighbours of the given coordinate that meet the condition
// and a boolean result, false if any neighbours dont meet the condition
func returnNeighboursThatMeetCondition(
	matrix [][]int,
	pos coordinate,
	includeDiagonals bool,
	condition func(original int, neighbour int) bool) ([]coordinate, bool) {

	minY := 0
	minX := 0
	maxY := len(matrix) - 1
	maxX := len(matrix[0]) - 1

	var neighbours []coordinate
	allNeighboursMeetCondition := true

	for subY := pos.y - 1; subY <= pos.y+1; subY++ {
		for subX := pos.x - 1; subX <= pos.x+1; subX++ {
			// matrix bounds
			if subX < minX || subX > maxX || subY < minY || subY > maxY {
				continue
			}

			// diagonals
			if (subY != pos.y && subX != pos.x) && !includeDiagonals {
				continue
			}

			// ignore the original coordinate
			if pos.x == subX && pos.y == subY {
				continue
			}

			if condition(matrix[pos.y][pos.x], matrix[subY][subX]) {
				neighbours = append(neighbours, coordinate{subX, subY})
			} else {
				allNeighboursMeetCondition = false
			}
		}
	}

	return neighbours, allNeighboursMeetCondition
}

func findAllLocalMinima(matrix [][]int) map[string]positionData {

	localMinimaMap := make(map[string]positionData)

	minY := 0
	minX := 0
	maxY := len(matrix)
	maxX := len(matrix[0])

	for y := minY; y < maxY; y++ {
		for x := minX; x < maxX; x++ {

			_, conditionMet := returnNeighboursThatMeetCondition(matrix,
				coordinate{x, y},
				false,
				func(original, neighbour int) bool {
					return original < neighbour
				})

			if conditionMet {
				key := fmt.Sprintf("%d-%d", x, y)
				localMinimaMap[key] = positionData{coordinate{x, y}, matrix[y][x]}
			}
		}
	}

	return localMinimaMap
}

func findPathsFlowingUpFromPositions(positions map[string]positionData, matrix [][]int) []map[string]*positionFrequency {

	var allBasins []map[string]*positionFrequency

	for key, posData := range positions {
		var positionsInBasin map[string]*positionFrequency
		positionsInBasin = make(map[string]*positionFrequency)
		// add itself
		positionsInBasin[key] = &positionFrequency{posData, 1}

		// find neighbours of root node
		neighbours, _ := returnNeighboursThatMeetCondition(matrix, posData.pos, false, neighbourFlowsUpCondition)

		// recurse all other neighbours
		for _, neighbour := range neighbours {
			neighbourFrequency := &positionFrequency{positionData{neighbour, matrix[neighbour.y][neighbour.x]}, 1}
			positionsInBasin[coordinateToKey(neighbour)] = neighbourFrequency
			findPathsFlowingUpRecursive(neighbour, positionsInBasin, matrix)
		}

		allBasins = append(allBasins, positionsInBasin)
	}

	return allBasins
}

func findPathsFlowingUpRecursive(pos coordinate, positionsInBasin map[string]*positionFrequency, matrix [][]int) {
	neighbours, _ := returnNeighboursThatMeetCondition(matrix, pos, false, neighbourFlowsUpCondition)

	for _, neighbour := range neighbours {
		key := coordinateToKey(neighbour)
		if _, found := positionsInBasin[key]; !found {
			neighbourFrequency := &positionFrequency{positionData{neighbour, matrix[neighbour.y][neighbour.x]}, 1}
			positionsInBasin[key] = neighbourFrequency
		} else {
			positionsInBasin[key].count++
		}

		findPathsFlowingUpRecursive(neighbour, positionsInBasin, matrix)
	}
}

func writeHeightMapAndBasinsToFile(matrix [][]int, lowPoints map[string]positionData, basins []map[string]*positionFrequency, filename string) {
	file, err := os.Create(fmt.Sprintf("%s.png", filename))

	utilities.CheckError(err)

	defer file.Close()

	maxX := len(matrix[0])
	maxY := len(matrix)
	image := image.NewRGBA(image.Rect(0, 0, maxX, maxY))

	colorStep := uint8(255 / 9)

	for y := 0; y < maxY; y++ {
		for x := 0; x < maxX; x++ {
			col := color.RGBA{colorStep * uint8(matrix[y][x]), 0, 0, 255}
			image.Set(x, y, col)
		}
	}

	for _, posData := range lowPoints {
		col := color.RGBA{0, 255, 255, 255}
		image.Set(posData.pos.x, posData.pos.y, col)
	}

	for _, basin := range basins {
		for _, point := range basin {
			col := color.RGBA{0, colorStep * uint8(point.posData.val), 0, 255}
			image.Set(point.posData.pos.x, point.posData.pos.y, col)
		}
	}

	png.Encode(file, image)
}

func main() {
	matrix, err := utilities.ReadFileAndSplitLinesIntoMatrixI("input", "")

	utilities.CheckError(err)

	lowPoints := findAllLocalMinima(matrix)

	riskLevel := 0
	for _, point := range lowPoints {
		riskLevel += point.val + 1
	}

	fmt.Printf("Total Risk Level: %d\n", riskLevel)

	basins := findPathsFlowingUpFromPositions(lowPoints, matrix)

	sort.Slice(basins, func(i, j int) bool {
		return len(basins[i]) > len(basins[j])
	})

	prodBasinSize := 1
	for i := 0; i < 3; i++ {
		prodBasinSize *= len(basins[i])
	}

	writeHeightMapAndBasinsToFile(matrix, lowPoints, basins, "heightmap")
	fmt.Printf("3 Largest Basin Sizes Product: %d\n", prodBasinSize)
}
