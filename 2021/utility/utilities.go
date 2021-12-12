package utilities

import (
	"bufio"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
)

// files

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

// constructs a matrix line by line, each row made by splitting said line into a slice
func ReadFileAndSplitLinesIntoMatrixI(path string, delimiter string) ([][]int, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}

	defer file.Close()

	var matrix [][]int
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lineSplit := StringSliceToIntSlice(strings.Split(scanner.Text(), delimiter))

		matrix = append(matrix, lineSplit)

	}

	return matrix, scanner.Err()
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

// slice operations

func StringSliceToIntSlice(input []string) []int {
	var output []int
	for _, element := range input {
		elementAsInt, err := strconv.Atoi(element)
		CheckError(err)

		output = append(output, elementAsInt)
	}

	return output
}

func RemoveDuplicatesISlice(input []int) []int {
	dupMap := make(map[int]bool)
	var cleanSlice []int
	for _, num := range input {
		if _, found := dupMap[num]; !found {
			dupMap[num] = true
			cleanSlice = append(cleanSlice, num)
		}
	}

	return cleanSlice
}

// error helpers
func CheckError(err error) {
	if err != nil {
		panic(err)
	}
}

// maths

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

// should be unsigned really but cba with conversions
func AbsI(val int) int {
	if val < 0 {
		return val * -1
	} else {
		return val
	}
}

// string stuff

func StrLen(s string) int {
	return len([]rune(s))
}

func StrDiff(a string, b string) string {
	sb := new(strings.Builder)
	foundMap := make(map[rune]struct{})

	var bigger string
	var smaller string

	if StrLen(a) >= StrLen(b) {
		bigger = a
		smaller = b
	} else {
		smaller = a
		bigger = b
	}

	for _, char := range smaller {
		foundMap[char] = struct{}{}
	}

	for _, char := range bigger {
		if _, found := foundMap[char]; !found {
			sb.WriteRune(char)
		}
	}

	return sb.String()
}
