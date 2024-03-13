package worker

/*
import (
	"bytes"
	"encoding/hex"
	"fmt"
	"github.com/hacash/core/blocks"
	"github.com/hacash/mint/difficulty"
	"github.com/hacash/x16rs"
	"sync"
	"sync/atomic"
)

func (g *GpuMiner) CloseUploadHashrate() {
}

func (g *GpuMiner) GetSuperveneWide() int {
	return len(g.devices)
}

func (g *GpuMiner) DoMining(blockHeight uint64, reporthashrate bool, stopmark *byte, tarhashvalue []byte, blockheadmeta [][]byte) (bool, int, []byte, []byte) {

	deviceNum := len(g.devices)
	//fmt.Print(overallstep)

	var successed bool = false
	var successMark uint32 = 0
	var successStuffIdx int = 0
	var successNonce []byte = nil
	var successHash []byte = nil


	var syncWait = sync.WaitGroup{}
	syncWait.Add(deviceNum)


	for i := 0; i < deviceNum; i++ {
		go func(did int) {
			defer syncWait.Done()
			//fmt.Println("mr.deviceworkers[i]", did, len(g.deviceworkers), g.deviceworkers)
			//devideCtx := g.deviceworkers[did]
			stuffbts := blockheadmeta[did]
			//
			x16rsrepeat := uint32(x16rs.HashRepeatForBlockHeight(blockHeight))
			var basenoncestart uint64 = 1
		RUNMINING:
			//
			//devideCtx := g.createWorkContext(did)
			devideCtx := g.deviceworkers[did]
			devideCtx.ReInit(stuffbts, tarhashvalue)
			//fmt.Println("DO RUNMINING...")
			//ttstart := time.Now()
			groupsize := g.devices[did].MaxWorkGroupSize()
			if g.groupSize > 0 {
				groupsize = int(g.groupSize)
			}
			globalwide := groupsize * g.groupNum
			overstep := globalwide * g.itemLoop // nonce
			//fmt.Println(overstep, groupsize)
			success, nonce, endhash := g.doGroupWork(devideCtx, globalwide, groupsize, x16rsrepeat, uint32(basenoncestart))
			//devideCtx.Release() //
			fmt.Print("_")
			//fmt.Println("END RUNMINING:", time.Now().Unix(), time.Now().Unix() - ttstart.Unix(), success, hex.EncodeToString(nonce), hex.EncodeToString(endhash) )
			if success && atomic.CompareAndSwapUint32(&successMark, 0, 1) {
				successed = true
				*stopmark = 1
				successStuffIdx = did
				successNonce = nonce
				successHash = endhash
				//
				blk, _, _ := blocks.ParseExcludeTransactions(stuffbts, 0)
				blk.SetNonceByte(nonce)
				nblkhx := blk.HashFresh()
				if difficulty.CheckHashDifficultySatisfy(nblkhx, tarhashvalue) == false || bytes.Compare(nblkhx, endhash) != 0 {
					//fmt.Println("")
					fmt.Println(nblkhx.ToHex(), hex.EncodeToString(endhash))
					fmt.Println(hex.EncodeToString(stuffbts))
				}

				return // success
			}
			if *stopmark == 1 {
				//fmt.Println("ok.")
				return //
			}
			//
			basenoncestart += uint64(overstep)
			if basenoncestart > uint64(4294967295) {
				//if basenoncestart > uint64(529490) {
				return //
			}
			//time.Sleep(time.Second * 5)
			goto RUNMINING
		}(i)
	}

	//fmt.Println("syncWait.Wait()")
	//
	syncWait.Wait()

	//fmt.Println("syncWait.Wait() ok ")

	//
	return successed, successStuffIdx, successNonce, successHash

}
*/
