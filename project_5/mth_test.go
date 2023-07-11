/*
Copyright 2019-2020 vChain, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

package merkletree

import (
	"crypto/sha256"
	"fmt"
	"strconv"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMTH(t *testing.T) {

	D := [][]byte{}
	assert.Equal(t, sha256.Sum256(nil), MTH(D))
	for index := uint64(0); index <= 64; index++ {
		b := []byte(strconv.FormatUint(index, 10))
		D = append(D, b)
		assert.Equal(t, testRoots[index], MTH(D))
	}
}

func TestMPath(t *testing.T) {

	D := [][]byte{}

	assert.Nil(t, MPath(0, D)) // undefined path

	for index := uint64(0); index <= 8; index++ {
		b := []byte(strconv.FormatUint(index, 10))
		D = append(D, b)

		assert.Nil(t, MPath(index+1, D)) // undefined path

		for i := uint64(0); i <= index; i++ {
			fmt.Println("\n\n-------- TEST", index+1, "--------")
			path := MPath(i, D)
			fmt.Printf(" len(path)=%d\n", len(path))
			for d, h := range path {
				fmt.Printf("%d) %.2x\n", d, h[0])
			}
			assert.Equal(t, testPaths[index][i], path)
		}
	}
}

func TestMProof(t *testing.T) {

	D := [][]byte{}

	assert.Nil(t, MProof(0, D)) // undefined proof

	for index := uint64(0); index <= 8; index++ {
		b := []byte(strconv.FormatUint(index, 10))
		D = append(D, b)

		assert.Nil(t, MProof(index+1, D)) // undefined proof

		fmt.Println("\n\n-------- TEST", index+1, "--------")
		for i := uint64(0); i <= index; i++ {
			fmt.Printf("\nTEST n=%d i=%d", index+1, i)
			path := MProof(i, D)
			fmt.Printf(" len(path)=%d\n", len(path))
			for d, h := range path {
				fmt.Printf("%d) %.2x\n", d, h[0])
			}
			assert.Equal(t, testCPaths[index][i], path)
		}
	}
}

func BenchmarkMTH(b *testing.B) {
	D := [][]byte{}
	for i := 0; i < b.N; i++ {
		D = append(D, []byte{0, 1, 3, 4, 5, 6, 7})
		MTH(D)
	}
}
