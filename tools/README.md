# Tools

## heatmap.py

This Python script aids in visualizing the microarchitectural channels created by the covert channels.

**Usage:**

```bash
python3 heatmap.py [trace | pruned_matrix | pruned_matrix_paths | ch_matrix]
```
  
To plot the channels for each board/vendor, you can run, for example:

```bash
python3 heatmap.py ch_matrix NXP
```

**Reuslts**

The script will output the following files under the ``results_ch_matrix`` directory:
- `boardX_ch_matrix.png`: Channel matrix heatmap for each board.

## profile.py 

This Python script extracts the pruned matrix, which contains the clocks carrying side-channel information, from a trace of the victim.

**Usage:**

```bash 
python3 profile.py [prof_only_contention | prof_all | trace] [N_ACTIONS]
```  
- `prof_only_contention`: Return unique clocks for each action (only considering contention)
- `prof_all`: Return unique clocks for each action (with and without contention)
- `trace`: Generate trace with unique clocks for each action
- `N_ACTIONS`: Number of profiled actions you want to consider.

**Results**

The tool will output the results to `data_out.txt` file.