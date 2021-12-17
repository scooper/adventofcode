package main

import (
	utilities "adventofcode/utility/common"
	"adventofcode/utility/structures"
	"fmt"
	"image"
	"image/color"
	"image/color/palette"
	"image/gif"
	"os"
	"strconv"
	"strings"
)

func printMatrix(mat structures.Matrix) {
	m, n := mat.Size()

	for mi := 0; mi < m; mi++ {
		fmt.Printf("[ ")
		for ni := 0; ni < n; ni++ {
			fmt.Printf("%d ", mat.Get(mi, ni).(int))
		}
		fmt.Printf("]\n")
	}
}

func matrixToImage(mat structures.Matrix) *image.Paletted {
	m, n := mat.Size()

	colWeight := int(255 / 9)

	img := image.NewPaletted(image.Rect(0, 0, m, n), palette.WebSafe)

	for mi := 0; mi < m; mi++ {
		for ni := 0; ni < n; ni++ {
			val := mat.Get(mi, ni).(int)
			col := uint8(colWeight * val)
			img.Set(mi, ni, color.RGBA{col, col, col, 255})
		}
	}

	return img
}

func keyToPos(key string) (int, int) {
	split := strings.Split(key, "-")

	m, err := strconv.Atoi(split[0])
	n, err := strconv.Atoi(split[1])

	utilities.CheckError(err)

	return m, n
}

func posToKey(m, n int) string {
	return fmt.Sprintf("%d-%d", m, n)
}

func doFlash(m, n int, mat structures.Matrix, flashed map[string]int) {

	initKey := posToKey(m, n)
	if _, found := flashed[initKey]; found {
		return
	}

	flashed[posToKey(m, n)] += 1

	neighbours := mat.GetIndicesOfNeighbours(m, n, true)

	for key := range neighbours {
		neighbourM, neighbourN := keyToPos(key)
		mat.Set(neighbourM, neighbourN, mat.Get(neighbourM, neighbourN).(int)+1)
	}

	flashedNeighbours := mat.GetIndicesOfNeighboursMeetingCondition(m, n, true, func(original, neighbour interface{}) bool {
		return neighbour.(int) > 9
	})

	for key := range flashedNeighbours {
		neighbourM, neighbourN := keyToPos(key)
		if _, found := flashed[key]; !found {
			doFlash(neighbourM, neighbourN, mat, flashed)
		}
	}
}

func doStep(mat structures.Matrix) int {
	m, n := mat.Size()

	flashed := make(map[string]int)

	// increment everything
	for mi := 0; mi < m; mi++ {
		for ni := 0; ni < n; ni++ {
			// increase energy level by 1
			mat.Set(mi, ni, mat.Get(mi, ni).(int)+1)
		}
	}

	// flash if greater than 9 (recursive)
	for mi := 0; mi < m; mi++ {
		for ni := 0; ni < n; ni++ {
			if mat.Get(mi, ni).(int) > 9 {
				doFlash(mi, ni, mat, flashed)
			}
		}
	}

	// for everything that flashed, set to 0
	for key := range flashed {
		mi, ni := keyToPos(key)

		mat.Set(mi, ni, 0)
	}

	return len(flashed)
}

func main() {

	input, err := utilities.ReadFileAndSplitLinesIntoMatrixI("input", "")

	utilities.CheckError(err)

	matrix := structures.NewMatrixFromInput(input)

	printMatrix(matrix)
	fmt.Println()
	m, n := matrix.Size()

	step := 1

	var images []*image.Paletted
	flashesTotal := 0
	for true {
		flashesInStep := doStep(matrix)
		flashesTotal += flashesInStep
		//printMatrix(matrix)
		images = append(images, matrixToImage(matrix))
		//fmt.Println()
		if flashesInStep == (m * n) {
			fmt.Printf("Step %d: All flashed\n", step)
			break
		}
		step++
	}

	fmt.Printf("Total flashes over %d steps: %d", step, flashesTotal)

	file, err := os.Create("flashes.gif")

	utilities.CheckError(err)

	defer file.Close()

	gif.EncodeAll(file, &gif.GIF{
		Image: images,
		Delay: make([]int, step),
	})

}
