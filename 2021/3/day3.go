package main

import (
	utilities "adventofcode/utility/common"
	"fmt"
	"strconv"
	"strings"
)

func getPositiveBitCountOfValuesInPosition(values []string, position int) int {
	bit1count := 0
	for _, value := range values {
		bitConv := int(value[position] - '0')
		bit1count += bitConv
	}
	return bit1count
}

func getValuesWithBitInPosition(values []string, position int, bitChar byte) []string {
	var newValues []string

	for _, value := range values {
		if value[position] == bitChar {
			newValues = append(newValues, value)
		}
	}

	return newValues
}

func getValuesWithMostCommonBitsInPosition(values []string, position int, bias byte) []string {
	valuesLen := len(values)

	bit1count := getPositiveBitCountOfValuesInPosition(values, position)

	var lookup byte
	bit0count := valuesLen - bit1count
	if bit1count == bit0count {
		lookup = bias
	} else if bit1count > bit0count {
		lookup = '1'
	} else {
		lookup = '0'
	}

	return getValuesWithBitInPosition(values, position, lookup)
}

func getValuesWithLeastCommonBitsInPosition(values []string, position int, bias byte) []string {
	valuesLen := len(values)

	bit1count := getPositiveBitCountOfValuesInPosition(values, position)

	var lookup byte
	bit0count := valuesLen - bit1count
	if bit1count == bit0count {
		lookup = bias
	} else if bit1count > bit0count {
		lookup = '0'
	} else {
		lookup = '1'
	}

	return getValuesWithBitInPosition(values, position, lookup)
}

func part1(values []string) {
	valuesLen := len(values)
	valueLen := len(values[0])

	var gammaBuilder strings.Builder
	gammaBuilder.WriteString("0b")
	var epsilonBuilder strings.Builder
	epsilonBuilder.WriteString("0b")

	bit1Occurances := make([]int, valueLen)
	for i := 0; i < valueLen; i++ {
		bit1Occurances[i] += getPositiveBitCountOfValuesInPosition(values, i)
	}

	for _, bit1Occurance := range bit1Occurances {
		bit0Occurance := valuesLen - bit1Occurance

		if bit0Occurance > bit1Occurance {
			gammaBuilder.WriteRune('0')
			epsilonBuilder.WriteRune('1')
		} else {
			gammaBuilder.WriteRune('1')
			epsilonBuilder.WriteRune('0')
		}
	}

	gamma, gbIntErr := strconv.ParseInt(gammaBuilder.String(), 0, 0)
	utilities.CheckError(gbIntErr)
	epsilon, ebIntErr := strconv.ParseInt(epsilonBuilder.String(), 0, 0)
	utilities.CheckError(ebIntErr)

	fmt.Printf("Gamma: %d, Epsilon: %d. Multiplied: %d\n", gamma, epsilon, gamma*epsilon)
}

func part2(values []string) {
	ogrStr := ""
	c02srStr := ""

	tempValuesOgr := values
	tempValuesC02sr := values
	for i := 0; i < len(values[0]); i++ {
		// oxygen
		tempValuesOgr = getValuesWithMostCommonBitsInPosition(tempValuesOgr, i, '1')
		if len(tempValuesOgr) == 1 {
			ogrStr = tempValuesOgr[0]
		}
		// co2
		tempValuesC02sr = getValuesWithLeastCommonBitsInPosition(tempValuesC02sr, i, '0')
		if len(tempValuesC02sr) == 1 {
			c02srStr = tempValuesC02sr[0]
		}

		if len(ogrStr) != 0 && len(c02srStr) != 0 {
			break
		}
	}

	ogr, ogrIntErr := strconv.ParseInt(ogrStr, 2, 0)
	utilities.CheckError(ogrIntErr)
	c02sr, c02IntErr := strconv.ParseInt(c02srStr, 2, 0)
	utilities.CheckError(c02IntErr)

	fmt.Printf("Oxygen GR: %d, C02 SR: %d. Multiplied: %d\n", ogr, c02sr, ogr*c02sr)
}

func main() {
	lines, err := utilities.ReadFileIntoSliceString("input")
	utilities.CheckError(err)

	part1(lines)
	part2(lines)
}
