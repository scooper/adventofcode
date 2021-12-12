package main

import (
	utilities "adventofcode/utility"
	"fmt"
	"sort"
	"strings"
)

type display struct {
	scrambledSegments []string
	output            []string
}

func findNumUniqueNumberSegmentOutputs(displays []display) map[int]int {
	uniqueCountMap := make(map[int]int)
	for i, display := range displays {
		for _, number := range display.output {
			switch len(number) {
			case 2:
				fallthrough
			case 3:
				fallthrough
			case 4:
				fallthrough
			case 7:
				if _, found := uniqueCountMap[i]; !found {
					uniqueCountMap[i] = 1
				} else {
					uniqueCountMap[i]++
				}

			}
		}

	}

	return uniqueCountMap
}

func notBit(number int) int {
	return ^number & 1
}

func changeBit(in int, pos uint, bit int) int {
	if bit == 0 {
		mask := ^(1 << pos)
		in &= mask
	} else {
		in |= (1 << pos)
	}
	return in
}

// given number in the format ABCD (4 bits)
func segmentsLitFromNumber(number int) int {

	A := (number & 8) >> 3
	B := (number & 4) >> 2
	C := (number & 2) >> 1
	D := (number & 1) >> 0

	a := C | A | (notBit(B) & notBit(D)) | (B & D)
	b := A | (notBit(C) & notBit(D)) | (B & notBit(C)) | (B & notBit(D))
	c := notBit(B) | (notBit(C) & notBit(D)) | (C & D)
	d := A | (notBit(B) & C) | (C & notBit(D)) | (B & notBit(C))
	e := (notBit(B) & notBit(D)) | (C & notBit(D))
	f := notBit(C) | D | B
	g := A | (notBit(B) & notBit(D)) | (notBit(B) & C) | (C & notBit(D)) | (B & notBit(C) & D)

	baseMask := 0b0

	baseMask = changeBit(baseMask, 0, g)
	baseMask = changeBit(baseMask, 1, f)
	baseMask = changeBit(baseMask, 2, e)
	baseMask = changeBit(baseMask, 3, d)
	baseMask = changeBit(baseMask, 4, c)
	baseMask = changeBit(baseMask, 5, b)
	baseMask = changeBit(baseMask, 6, a)

	return baseMask
}

func strMapValsToStr(strMap map[string]string) string {
	sb := new(strings.Builder)

	for _, val := range strMap {
		sb.WriteString(val)
	}

	return sb.String()
}

func decodeDisplay(segments []string) map[string]int {

	mixedSegmentsToNumber := map[string]int{segments[0]: 1, segments[1]: 7, segments[2]: 4, segments[9]: 8}
	connectionMapping := make(map[string]string)

	// compare 1(2) and 7(3), difference is 'a'
	connectionMapping["a"] = utilities.StrDiff(segments[0], segments[1])

	// find out which element 6 is
	var six string
	var otherLen6s []string
	for _, len6 := range []string{segments[6], segments[7], segments[8]} {
		// difference between element and 1(2)
		diff := utilities.StrDiff(len6, segments[0])

		if utilities.StrLen(diff) == 5 {
			six = len6
			mixedSegmentsToNumber[six] = 6
		} else {
			otherLen6s = append(otherLen6s, len6)
		}
	}

	// c is found by comparing our found 6 with 8
	connectionMapping["c"] = utilities.StrDiff(six, segments[9])

	// search len 5s to find e and the other 5s
	//var five string
	var otherLen5s []string
	for _, len5 := range []string{segments[3], segments[4], segments[5]} {
		// difference between element and 6
		diff := utilities.StrDiff(len5, six)

		if utilities.StrLen(diff) == 1 {
			//five = len5
			mixedSegmentsToNumber[len5] = 5
			connectionMapping["e"] = diff
		} else {
			otherLen5s = append(otherLen5s, len5)
		}
	}

	var zero string
	for i, len6 := range otherLen6s {
		if strings.Contains(len6, connectionMapping["e"]) {
			zero = len6
			mixedSegmentsToNumber[zero] = 0
			nine := otherLen6s[(i+1)%2]
			mixedSegmentsToNumber[nine] = 9
			break
		}
	}

	connectionMapping["d"] = utilities.StrDiff(zero, segments[9])

	for i, len5 := range otherLen5s {
		currentFound := strMapValsToStr(connectionMapping)
		diff := utilities.StrDiff(currentFound, len5)

		if utilities.StrLen(diff) == 1 {
			mixedSegmentsToNumber[len5] = 2
			mixedSegmentsToNumber[otherLen5s[(i+1)%2]] = 3
			break
		}
	}

	return mixedSegmentsToNumber
}

func orderStringAplhabetically(s string) string {
	if utilities.StrLen(s) == 1 {
		return s
	}

	stringRunes := []rune(s)
	sort.Slice(stringRunes, func(i, j int) bool {
		return stringRunes[i] < stringRunes[j]
	})

	return string(stringRunes)
}

func main() {
	input, err := utilities.ReadFileIntoSliceSplitString("input", " | ")
	utilities.CheckError(err)

	var displays []display

	for _, line := range input {
		scrambledSegmentsUnprocessed := strings.Fields(line[0])

		// put elements into alphabetical order
		var scrambledSegments []string
		for _, segment := range scrambledSegmentsUnprocessed {
			scrambledSegments = append(scrambledSegments, orderStringAplhabetically(segment))
		}

		// sort by length
		sort.Slice(scrambledSegments, func(i, j int) bool {
			return utilities.StrLen(scrambledSegments[i]) < utilities.StrLen(scrambledSegments[j])
		})

		outputUnprocessed := strings.Fields(line[1])
		var output []string
		for _, segment := range outputUnprocessed {
			output = append(output, orderStringAplhabetically(segment))
		}

		displayElement := display{scrambledSegments, output}

		displays = append(displays, displayElement)
	}

	uniqueCountMap := findNumUniqueNumberSegmentOutputs(displays)

	sumCounts := 0

	for _, count := range uniqueCountMap {
		sumCounts += count
	}

	fmt.Printf("Number of displays: %d\n", len(displays))
	fmt.Printf("Number of displays with unique segments in output: %d\n", len(uniqueCountMap))
	fmt.Printf("Count of unique number segments in output: %d\n\n", sumCounts)

	sumOutputs := 0
	for _, displayElement := range displays {
		decodeMap := decodeDisplay(displayElement.scrambledSegments)

		output := displayElement.output
		result := 0
		op := 1

		// join result numbers into correct positions
		for i := len(output) - 1; i >= 0; i-- {
			val := decodeMap[output[i]]
			result += val * op
			op *= 10
		}

		sumOutputs += result
		fmt.Printf("%v: %d\n", output, result)

	}

	fmt.Printf("Sum of outputs: %d", sumOutputs)
}
