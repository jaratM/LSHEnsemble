#include "linearscan_benchmark_test.hpp"
#include "lshensemble_benchmark_test.hpp"
#include "accuracy_benchmark_test.hpp"

constexpr int subsets[] {65537};
constexpr int subsetsLen {std::size(subsets)};
constexpr double threshold {0.5};
constexpr double fracQuery  {0.01};
constexpr int minDomainSize {10};


int readDomains(std::vector<rawDomain> &rawDomains, std::string const& dir){
    int count = 0;
    for (const auto & entry : std::filesystem::directory_iterator(dir)){
        std::ifstream infile(entry.path());
        std::string key = entry.path().filename();
        std::string value;
        std::map<std::string, bool> values;
        while (std::getline(infile, value))
        {
            std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c){ return std::tolower(c); });
            values[value] = true;
        }
        if(values.size() < minDomainSize) continue;
        count++;
        rawDomains.push_back({values, key});
    }
    return count;
}
void benchmarkCOD(rawDomain  *rawDomains, rawDomain  *queries, int n, int q, double threshold, int subset){
    std::string linearscanOutput = "../output32/cod_linearscan_threshold=" + std::to_string(threshold) + ",subset=" + std::to_string(n);
	std::string lshensembleOutput = "../output32/cod_lshensemble_threshold=" + std::to_string(threshold) + ",subset=" + std::to_string(n);
	std::string accuracyOutput = "../output32/cod_accuracy_threshold=" + std::to_string(threshold) + ",subset=" + std::to_string(n);
    benchmarkLinearscan(rawDomains, queries, n, q, threshold, linearscanOutput);
	benchmarkLshEnsemble(rawDomains, queries, n, q, threshold, lshensembleOutput);
	benchmarkAccuracy(linearscanOutput, lshensembleOutput, accuracyOutput);


}
int main(int argc, char* argv[]) {

    std::vector<rawDomain> rawDomains;

    clock_t begin = clock();
    int numDomains;
    // Running this function requires a `_cod_domains` directory
    // in the current directory.
    // The `_code_domains` directory should contain domains files,
    // which are line-separated files.
    numDomains = readDomains(rawDomains, "../doc_files");

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "read " << numDomains << " domains in " << elapsed_secs << "\n";

    // sort domains 
    std::sort(rawDomains.begin(), rawDomains.end(), &rawDomainSorter);

    int numQuery {int(fracQuery * double(numDomains))};
    std::cout << "size of queries" << numQuery <<"\n";
    // rawDomain rawDomains_[subsets[i]];
    // for (int k = 0; k < subsets[i]; k++) {
    //     rawDomains_[k] = rawDomains[k];
    // }
    rawDomain queries[numQuery];
    srand (benchmarkSeed);
    // int randlist[]={13471, 61330, 57826, 43794, 11151, 3508, 934, 24293, 63992, 8800, 46030, 56317, 33608, 8869, 62548, 57968, 3006, 24932, 49548, 3754, 5791, 59821, 45816, 39922, 22277, 64538, 54216, 25097, 52614, 15222, 25706, 41771, 35031, 32507, 46830, 41315, 5102, 6895, 19765, 12609, 30379, 24828, 49802, 32013, 37717, 13645, 28034, 36149, 21063, 35630, 53337, 31074, 30506, 32846, 43307, 52221, 58529, 10285, 58264, 36262, 22444, 40769, 32797, 57392, 14261, 31260, 4238, 50240, 62071, 65317, 6169, 14425, 6151, 33061, 7680, 48609, 60032, 27250, 49149, 31197, 28717, 38745, 20913, 28485, 20842, 9276, 49629, 30384, 55084, 16120, 61738, 55486, 11384, 47694, 31327, 22323, 36299, 9133, 39506, 22173, 10890, 31536, 42965, 15902, 38898, 34436, 11356, 51785, 4607, 43291, 62952, 37725, 31447, 27049, 5760, 15284, 64729, 44920, 62601, 62249, 21422, 19423, 65051, 35151, 4749, 6963, 51729, 53990, 6178, 62848, 65375, 48078, 14507, 21495, 977, 15627, 44068, 25199, 33036, 45513, 17072, 36586, 27364, 1886, 21814, 56950, 4866, 57087, 64351, 38989, 2947, 57257, 14822, 49245, 64278, 22272, 62644, 54652, 44748, 44101, 38942, 216, 44318, 11430, 36072, 60525, 35828, 35759, 1766, 37028, 51511, 22177, 41607, 47062, 4130, 47074, 48428, 63973, 18179, 13226, 45481, 28597, 55437, 51576, 8741, 18637, 34527, 64362, 32789, 48253, 40670, 45749, 58809, 61227, 13302, 55121, 55758, 38667, 2172, 48107, 29129, 27742, 4972, 34991, 44332, 53865, 37494, 63723, 57613, 37605, 47351, 56026, 13039, 49938, 22152, 14176, 48968, 32745, 6964, 28504, 37618, 40832, 57009, 13159, 21623, 10562, 1680, 7667, 4219, 45676, 12193, 17164, 8893, 33195, 22394, 59532, 11223, 53841, 48010, 55373, 58719, 11049, 11647, 16901, 17061, 5718, 51092, 58148, 14331, 62112, 21939, 7645, 2394, 60195, 25413, 42313, 45658, 29710, 10416, 6273, 48324, 48758, 59654, 28568, 31199, 55126, 12449, 39325, 42933, 19343, 8089, 32213, 21989, 35090, 24740, 11255, 29188, 22059, 36974, 60935, 16457, 63678, 55426, 39723, 22143, 17592, 37101, 8763, 35600, 14451, 22412, 38548, 28158, 62569, 26152, 4132, 51661, 59571, 24961, 23919, 34572, 36698, 63774, 62074, 44379, 32416, 25286, 9485, 3510, 45535, 53968, 22248, 61351, 10392, 40475, 31865, 32100, 33156, 37572, 14893, 65492, 59583, 55510, 51768, 60110, 38525, 58609, 29026, 62429, 28630, 58214, 45761, 25503, 26330, 51579, 38750, 9903, 4006, 29448, 38199, 1367, 16756, 21823, 56843, 7471, 28498, 26369, 7815, 11957, 17124, 19901, 16153, 15564, 24212, 11004, 31169, 26462, 8880, 21013, 46397, 5979, 52828, 984, 47308, 41150, 40484, 5459, 11176, 51147, 63209, 13164, 4222, 64977, 21605, 50605, 44800, 64505, 16065, 35339, 10624, 62749, 24457, 41502, 46627, 43190, 37918, 9188, 38250, 46718, 47906, 50220, 39569, 57394, 64593, 48655, 37449, 31532, 53703, 62610, 55239, 47762, 14216, 42115, 11843, 54969, 23995, 58950, 57380, 46565, 50068, 29477, 13511, 9535, 58224, 53451, 43183, 45226, 51309, 4618, 18189, 54794, 61862, 9883, 55468, 9988, 2487, 64797, 30553, 25305, 10135, 45765, 35898, 16547, 8682, 52312, 15368, 1387, 14812, 50966, 36887, 4906, 41193, 37254, 35485, 27793, 64770, 46194, 9251, 7452, 48526, 29440, 354, 595, 2509, 65507, 37437, 62081, 17237, 30772, 6480, 50451, 12116, 63505, 62389, 59439, 58846, 21547, 34787, 44645, 40176, 12407, 47957, 40197, 38756, 5900, 10372, 9016, 6323, 63381, 42431, 5094, 16578, 28631, 55720, 59722, 50852, 44940, 15223, 61780, 18592, 61198, 27422, 13459, 51217, 59030, 31613, 56335, 10022, 7574, 27833, 24168, 5604, 7167, 32493, 26327, 16768, 10207, 57936, 40546, 43103, 32980, 20158, 6360, 51450, 63639, 7583, 13641, 28481, 63513, 24466, 34971, 55810, 601, 55882, 8700, 16043, 23088, 35866, 13015, 33318, 8061, 28426, 55162, 5875, 2162, 8548, 57899, 61235, 23774, 3069, 55807, 65240, 5654, 36751, 46029, 52533, 42428, 40233, 22989, 12460, 59634, 31021, 62748, 61492, 58261, 45390, 22620, 49022, 35668, 15405, 6898, 65046, 49689, 22475, 59529, 48873, 39656, 31875, 46779, 39826, 2923, 49454, 61348, 42137, 30002, 2037, 7604, 55276, 40886, 51532, 7956, 5729, 49133, 35525, 22106, 26252, 18571, 22404, 38304, 4760, 38145, 9590, 57748, 31403, 32321, 59028, 5945, 22651, 8742, 64587, 54194, 12390, 55488, 57140, 55776, 13389, 42623, 65047, 25011, 61245, 29549, 5413, 54307, 64407, 19885, 45902, 11265, 16466, 60639, 17438, 38467, 25499, 11611, 44798, 27357, 48166, 60760, 12430, 44280, 11388, 39987, 47099, 36011, 62561, 44108, 13181, 34997, 38455, 30040, 59277, 27959, 61470, 3373, 24842, 12041, 30459, 39918, 60512, 56528, 49068, 51986, 11696, 40642, 59567, 23585};

    for(int j = 0; j < numQuery; j++){
        queries[j] = rawDomains[rand() % numDomains];
    }
    // Run benchmark
    std::cout << "start benchmark \n";
    benchmarkCOD(rawDomains.data(), queries, numDomains, numQuery, threshold, 1);
    
}


