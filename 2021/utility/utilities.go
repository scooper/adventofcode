package utilities

import (
	"bufio"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
)

func ReadFileIntoSliceI(path string) ([]int, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}

	defer file.Close()

	var lines []int
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lineInt, err := strconv.Atoi(scanner.Text())
		if err != nil {
			return nil, err
		}
		lines = append(lines, lineInt)
	}

	return lines, scanner.Err()
}

func ReadFileIntoSliceF64(path string) ([]float64, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}

	defer file.Close()

	var lines []float64
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lineFloat, err := strconv.ParseFloat(scanner.Text(), 32)
		if err != nil {
			return nil, err
		}
		lines = append(lines, lineFloat)
	}

	return lines, scanner.Err()
}

func ReadFileIntoSliceString(path string) ([]string, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}

	defer file.Close()

	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())

	}

	return lines, scanner.Err()
}

func ReadFileIntoSliceSplitString(path string, delimiter string) ([][]string, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}

	defer file.Close()

	var lines [][]string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lineSplit := strings.Split(scanner.Text(), delimiter)

		lines = append(lines, lineSplit)

	}

	return lines, scanner.Err()
}

func SplitFileByDelimiter(path string, delimiter string) ([]string, error) {
	fileContent, err := ioutil.ReadFile(path)

	if err != nil {
		return nil, err
	}

	// remove carriage returns so they dont screw up byte->string conversion
	return strings.Split(strings.ReplaceAll(string(fileContent), "\r", ""), delimiter), nil
}

func StringSliceToIntSlice(input []string) []int {
	var output []int
	for _, element := range input {
		elementAsInt, err := strconv.Atoi(element)
		CheckError(err)

		output = append(output, elementAsInt)
	}

	return output
}

func CheckError(err error) {
	if err != nil {
		panic(err)
	}
}

func MaxI(a int, b int) int {
	if a > b {
		return a
	} else {
		return b
	}
}

func MinI(a int, b int) int {
	if a < b {
		return a
	} else {
		return b
	}
}
