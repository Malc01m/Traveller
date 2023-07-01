namespace Comparators {
    /**
     * Finds the closer of two given numbers to a given number
     * 
     * @param query The number we need to know which of two numbers is closer to
     * @param lower The lower number for comparison
     * @param upper The higher number for comparison
     * @return pointer to the instance of the closer bound, or 
     *         nullptr if equidistant
     */
    int* closerTo(int query, int lower, int upper) {
        int* result;
        int lowerDiff = query - lower;
        int upperDiff = upper - query;
        if (lowerDiff < upperDiff) {
            result = &upper;
            return result;
        } else if (upperDiff < lowerDiff) {
            result = &lower;
            return result;
        } else {
            return nullptr;
        }
    }
}