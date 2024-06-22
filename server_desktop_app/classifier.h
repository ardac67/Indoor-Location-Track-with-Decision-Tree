#ifndef UUID139870285284736
#define UUID139870285284736
#include <QObject>
#include <QWidget>
#include <chrono>
class Classifier {
public:
    int predict(float * x) {
        int predictedValue = 0;
        auto startedAt = std::chrono::high_resolution_clock::now();
        uint16_t votes[10] = {
            0
        };
        uint8_t classIdx = 0;
        float classScore = 0;
        tree0(x, & classIdx, & classScore);
        votes[classIdx] += classScore;
        tree1(x, & classIdx, & classScore);
        votes[classIdx] += classScore;
        tree2(x, & classIdx, & classScore);
        votes[classIdx] += classScore;
        tree3(x, & classIdx, & classScore);
        votes[classIdx] += classScore;
        tree4(x, & classIdx, & classScore);
        votes[classIdx] += classScore;
        tree5(x, & classIdx, & classScore);
        votes[classIdx] += classScore;
        tree6(x, & classIdx, & classScore);
        votes[classIdx] += classScore;
        tree7(x, & classIdx, & classScore);
        votes[classIdx] += classScore;
        tree8(x, & classIdx, & classScore);
        votes[classIdx] += classScore;
        tree9(x, & classIdx, & classScore);
        votes[classIdx] += classScore;
        uint8_t maxClassIdx = 0;
        float maxVote = votes[0];
        for (uint8_t i = 1; i < 10; i++) {
            if (votes[i] > maxVote) {
                maxClassIdx = i;
                maxVote = votes[i];
            }
        }
        predictedValue = maxClassIdx;
        auto endedAt = std::chrono::high_resolution_clock::now();
        latency = std::chrono::duration_cast<std::chrono::microseconds>(endedAt - startedAt).count();
        return (lastPrediction = predictedValue);
    }
    uint32_t latencyInMicros() {
        return latency;
    }
    uint16_t latencyInMillis() {
        return latency / 1000;
    }
protected: float latency = 0;int lastPrediction = 0; void tree0(float * x, uint8_t * classIdx, float * classScore) {
        if (x[9] < -16.5) {
            if (x[3] < -80.5) {
                if (x[8] < -67.5) {
                    if (x[2] < -76.5) {
                        if (x[9] < -82.0) {
                            if (x[5] < -70.5) {
                                * classIdx = 5;* classScore = 19.0;
                                return;
                            } else {
                                * classIdx = 6;* classScore = 25.0;
                                return;
                            }
                        } else {
                            * classIdx = 5;* classScore = 19.0;
                            return;
                        }
                    } else {
                        if (x[3] < -82.0) {
                            if (x[9] < -73.5) {
                                if (x[3] < -84.0) {
                                    * classIdx = 6;* classScore = 25.0;
                                    return;
                                } else {
                                    * classIdx = 5;* classScore = 19.0;
                                    return;
                                }
                            } else {
                                * classIdx = 5;* classScore = 19.0;
                                return;
                            }
                        } else {
                            * classIdx = 6;* classScore = 25.0;
                            return;
                        }
                    }
                } else {
                    if (x[4] < -74.0) {
                        if (x[4] < -78.5) {
                            if (x[8] < -33.5) {
                                * classIdx = 8;* classScore = 34.0;
                                return;
                            } else {
                                if (x[0] < -91.5) {
                                    * classIdx = 6;* classScore = 25.0;
                                    return;
                                } else {
                                    * classIdx = 2;* classScore = 20.0;
                                    return;
                                }
                            }
                        } else {
                            * classIdx = 3;* classScore = 24.0;
                            return;
                        }
                    } else {
                        if (x[2] < -74.5) {
                            * classIdx = 4;* classScore = 39.0;
                            return;
                        } else {
                            * classIdx = 5;* classScore = 19.0;
                            return;
                        }
                    }
                }
            } else {
                if (x[4] < -66.5) {
                    if (x[5] < -77.0) {
                        if (x[0] < -42.5) {
                            if (x[0] < -86.0) {
                                if (x[9] < -90.0) {
                                    * classIdx = 1;* classScore = 24.0;
                                    return;
                                } else {
                                    * classIdx = 2;* classScore = 20.0;
                                    return;
                                }
                            } else {
                                * classIdx = 1;* classScore = 24.0;
                                return;
                            }
                        } else {
                            if (x[9] < -85.5) {
                                if (x[2] < -68.0) {
                                    * classIdx = 3;* classScore = 24.0;
                                    return;
                                } else {
                                    * classIdx = 2;* classScore = 20.0;
                                    return;
                                }
                            } else {
                                * classIdx = 3;* classScore = 24.0;
                                return;
                            }
                        }
                    } else {
                        if (x[9] < -64.0) {
                            if (x[9] < -86.0) {
                                * classIdx = 6;* classScore = 25.0;
                                return;
                            } else {
                                if (x[0] < -87.5) {
                                    * classIdx = 2;* classScore = 20.0;
                                    return;
                                } else {
                                    if (x[3] < -74.5) {
                                        * classIdx = 5;* classScore = 19.0;
                                        return;
                                    } else {
                                        * classIdx = 4;* classScore = 39.0;
                                        return;
                                    }
                                }
                            }
                        } else {
                            * classIdx = 9;* classScore = 28.0;
                            return;
                        }
                    }
                } else {
                    if (x[5] < -61.5) {
                        if (x[3] < -69.5) {
                            if (x[4] < -27.5) {
                                * classIdx = 4;* classScore = 39.0;
                                return;
                            } else {
                                if (x[9] < -91.5) {
                                    * classIdx = 1;* classScore = 24.0;
                                    return;
                                } else {
                                    * classIdx = 2;* classScore = 20.0;
                                    return;
                                }
                            }
                        } else {
                            * classIdx = 9;* classScore = 28.0;
                            return;
                        }
                    } else {
                        if (x[1] < -44.5) {
                            if (x[9] < -64.0) {
                                * classIdx = 5;* classScore = 19.0;
                                return;
                            } else {
                                * classIdx = 9;* classScore = 28.0;
                                return;
                            }
                        } else {
                            if (x[9] < -71.0) {
                                if (x[4] < -61.5) {
                                    * classIdx = 5;* classScore = 19.0;
                                    return;
                                } else {
                                    * classIdx = 4;* classScore = 39.0;
                                    return;
                                }
                            } else {
                                * classIdx = 4;* classScore = 39.0;
                                return;
                            }
                        }
                    }
                }
            }
        } else {
            if (x[8] < -75.5) {
                if (x[3] < -91.5) {
                    * classIdx = 8;* classScore = 34.0;
                    return;
                } else {
                    if (x[7] < -29.5) {
                        * classIdx = 7;* classScore = 4.0;
                        return;
                    } else {
                        if (x[2] < -74.5) {
                            if (x[8] < -90.5) {
                                * classIdx = 1;* classScore = 24.0;
                                return;
                            } else {
                                if (x[1] < -33.5) {
                                    * classIdx = 0;* classScore = 25.0;
                                    return;
                                } else {
                                    * classIdx = 8;* classScore = 34.0;
                                    return;
                                }
                            }
                        } else {
                            if (x[5] < -40.5) {
                                if (x[0] < -74.0) {
                                    * classIdx = 1;* classScore = 24.0;
                                    return;
                                } else {
                                    if (x[1] < -73.0) {
                                        * classIdx = 1;* classScore = 24.0;
                                        return;
                                    } else {
                                        * classIdx = 0;* classScore = 25.0;
                                        return;
                                    }
                                }
                            } else {
                                * classIdx = 0;* classScore = 25.0;
                                return;
                            }
                        }
                    }
                }
            } else {
                if (x[5] < -91.5) {
                    if (x[0] < -75.0) {
                        * classIdx = 8;* classScore = 34.0;
                        return;
                    } else {
                        * classIdx = 0;* classScore = 25.0;
                        return;
                    }
                } else {
                    if (x[3] < -39.0) {
                        if (x[2] < -78.5) {
                            * classIdx = 8;* classScore = 34.0;
                            return;
                        } else {
                            if (x[1] < -36.0) {
                                if (x[3] < -81.0) {
                                    * classIdx = 0;* classScore = 25.0;
                                    return;
                                } else {
                                    * classIdx = 1;* classScore = 24.0;
                                    return;
                                }
                            } else {
                                * classIdx = 8;* classScore = 34.0;
                                return;
                            }
                        }
                    } else {
                        * classIdx = 8;* classScore = 34.0;
                        return;
                    }
                }
            }
        }
    }
    void tree1(float * x, uint8_t * classIdx, float * classScore) {
        if (x[3] < -74.5) {
            if (x[1] < -31.5) {
                if (x[0] < -76.5) {
                    if (x[1] < -78.0) {
                        if (x[1] < -79.5) {
                            if (x[3] < -78.5) {
                                if (x[2] < -78.5) {
                                    if (x[0] < -84.5) {
                                        * classIdx = 7;* classScore = 13.0;
                                        return;
                                    } else {
                                        * classIdx = 8;* classScore = 22.0;
                                        return;
                                    }
                                } else {
                                    if (x[5] < -64.0) {
                                        * classIdx = 2;* classScore = 13.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 28.0;
                                        return;
                                    }
                                }
                            } else {
                                if (x[4] < -88.5) {
                                    * classIdx = 2;* classScore = 13.0;
                                    return;
                                } else {
                                    * classIdx = 1;* classScore = 22.0;
                                    return;
                                }
                            }
                        } else {
                            * classIdx = 6;* classScore = 25.0;
                            return;
                        }
                    } else {
                        if (x[3] < -83.0) {
                            * classIdx = 1;* classScore = 22.0;
                            return;
                        } else {
                            if (x[8] < -79.5) {
                                * classIdx = 1;* classScore = 22.0;
                                return;
                            } else {
                                if (x[1] < -73.5) {
                                    * classIdx = 0;* classScore = 19.0;
                                    return;
                                } else {
                                    if (x[2] < -65.0) {
                                        * classIdx = 1;* classScore = 22.0;
                                        return;
                                    } else {
                                        * classIdx = 2;* classScore = 13.0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (x[3] < -90.0) {
                        * classIdx = 8;* classScore = 22.0;
                        return;
                    } else {
                        if (x[0] < -30.5) {
                            if (x[3] < -75.5) {
                                if (x[1] < -69.0) {
                                    if (x[8] < -70.0) {
                                        * classIdx = 0;* classScore = 19.0;
                                        return;
                                    } else {
                                        * classIdx = 8;* classScore = 22.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 1;* classScore = 22.0;
                                    return;
                                }
                            } else {
                                * classIdx = 1;* classScore = 22.0;
                                return;
                            }
                        } else {
                            if (x[3] < -77.5) {
                                if (x[2] < -75.0) {
                                    * classIdx = 5;* classScore = 28.0;
                                    return;
                                } else {
                                    if (x[3] < -80.5) {
                                        * classIdx = 3;* classScore = 31.0;
                                        return;
                                    } else {
                                        * classIdx = 2;* classScore = 13.0;
                                        return;
                                    }
                                }
                            } else {
                                * classIdx = 3;* classScore = 31.0;
                                return;
                            }
                        }
                    }
                }
            } else {
                if (x[8] < -82.5) {
                    if (x[9] < -86.0) {
                        * classIdx = 6;* classScore = 25.0;
                        return;
                    } else {
                        if (x[0] < -92.5) {
                            * classIdx = 6;* classScore = 25.0;
                            return;
                        } else {
                            if (x[8] < -90.5) {
                                if (x[4] < -75.5) {
                                    * classIdx = 6;* classScore = 25.0;
                                    return;
                                } else {
                                    if (x[3] < -91.0) {
                                        * classIdx = 6;* classScore = 25.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 28.0;
                                        return;
                                    }
                                }
                            } else {
                                * classIdx = 5;* classScore = 28.0;
                                return;
                            }
                        }
                    }
                } else {
                    if (x[8] < -34.0) {
                        * classIdx = 6;* classScore = 25.0;
                        return;
                    } else {
                        if (x[9] < -64.0) {
                            if (x[3] < -84.5) {
                                if (x[9] < -81.5) {
                                    * classIdx = 6;* classScore = 25.0;
                                    return;
                                } else {
                                    * classIdx = 5;* classScore = 28.0;
                                    return;
                                }
                            } else {
                                if (x[9] < -71.5) {
                                    * classIdx = 5;* classScore = 28.0;
                                    return;
                                } else {
                                    if (x[2] < -71.0) {
                                        * classIdx = 4;* classScore = 46.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 28.0;
                                        return;
                                    }
                                }
                            }
                        } else {
                            * classIdx = 9;* classScore = 23.0;
                            return;
                        }
                    }
                }
            }
        } else {
            if (x[5] < -72.5) {
                if (x[0] < -35.5) {
                    if (x[8] < -75.5) {
                        if (x[6] < -32.5) {
                            * classIdx = 7;* classScore = 13.0;
                            return;
                        } else {
                            if (x[2] < -74.5) {
                                * classIdx = 0;* classScore = 19.0;
                                return;
                            } else {
                                if (x[2] < -59.5) {
                                    * classIdx = 2;* classScore = 13.0;
                                    return;
                                } else {
                                    * classIdx = 1;* classScore = 22.0;
                                    return;
                                }
                            }
                        }
                    } else {
                        if (x[5] < -80.5) {
                            * classIdx = 8;* classScore = 22.0;
                            return;
                        } else {
                            * classIdx = 2;* classScore = 13.0;
                            return;
                        }
                    }
                } else {
                    if (x[8] < -38.5) {
                        * classIdx = 7;* classScore = 13.0;
                        return;
                    } else {
                        if (x[9] < -83.0) {
                            if (x[2] < -65.0) {
                                * classIdx = 3;* classScore = 31.0;
                                return;
                            } else {
                                * classIdx = 2;* classScore = 13.0;
                                return;
                            }
                        } else {
                            if (x[1] < -88.0) {
                                * classIdx = 3;* classScore = 31.0;
                                return;
                            } else {
                                if (x[4] < -80.0) {
                                    * classIdx = 3;* classScore = 31.0;
                                    return;
                                } else {
                                    if (x[5] < -77.0) {
                                        * classIdx = 3;* classScore = 31.0;
                                        return;
                                    } else {
                                        * classIdx = 2;* classScore = 13.0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (x[9] < -60.0) {
                    if (x[9] < -83.0) {
                        if (x[9] < -90.0) {
                            * classIdx = 6;* classScore = 25.0;
                            return;
                        } else {
                            if (x[4] < -64.0) {
                                * classIdx = 6;* classScore = 25.0;
                                return;
                            } else {
                                * classIdx = 4;* classScore = 46.0;
                                return;
                            }
                        }
                    } else {
                        if (x[2] < -67.5) {
                            * classIdx = 4;* classScore = 46.0;
                            return;
                        } else {
                            if (x[5] < -59.0) {
                                * classIdx = 9;* classScore = 23.0;
                                return;
                            } else {
                                if (x[4] < -66.0) {
                                    * classIdx = 6;* classScore = 25.0;
                                    return;
                                } else {
                                    * classIdx = 4;* classScore = 46.0;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    if (x[5] < -27.5) {
                        if (x[1] < -43.5) {
                            * classIdx = 9;* classScore = 23.0;
                            return;
                        } else {
                            if (x[4] < -69.0) {
                                * classIdx = 9;* classScore = 23.0;
                                return;
                            } else {
                                * classIdx = 4;* classScore = 46.0;
                                return;
                            }
                        }
                    } else {
                        if (x[8] < -83.5) {
                            * classIdx = 7;* classScore = 13.0;
                            return;
                        } else {
                            if (x[0] < -74.0) {
                                * classIdx = 8;* classScore = 22.0;
                                return;
                            } else {
                                * classIdx = 0;* classScore = 19.0;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    void tree2(float * x, uint8_t * classIdx, float * classScore) {
        if (x[6] < -34.0) {
            * classIdx = 7;* classScore = 14.0;
            return;
        } else {
            if (x[0] < -30.5) {
                if (x[9] < -29.0) {
                    if (x[4] < -83.5) {
                        if (x[3] < -65.5) {
                            if (x[0] < -86.0) {
                                if (x[4] < -92.5) {
                                    if (x[5] < -85.0) {
                                        * classIdx = 1;* classScore = 25.0;
                                        return;
                                    } else {
                                        * classIdx = 2;* classScore = 19.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 2;* classScore = 19.0;
                                    return;
                                }
                            } else {
                                if (x[5] < -85.0) {
                                    * classIdx = 8;* classScore = 23.0;
                                    return;
                                } else {
                                    * classIdx = 1;* classScore = 25.0;
                                    return;
                                }
                            }
                        } else {
                            * classIdx = 3;* classScore = 27.0;
                            return;
                        }
                    } else {
                        if (x[9] < -76.5) {
                            if (x[9] < -90.5) {
                                * classIdx = 1;* classScore = 25.0;
                                return;
                            } else {
                                if (x[8] < -82.5) {
                                    if (x[4] < -76.5) {
                                        * classIdx = 5;* classScore = 24.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 24.0;
                                        return;
                                    }
                                } else {
                                    if (x[3] < -82.0) {
                                        * classIdx = 6;* classScore = 16.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 24.0;
                                        return;
                                    }
                                }
                            }
                        } else {
                            if (x[9] < -64.0) {
                                * classIdx = 5;* classScore = 24.0;
                                return;
                            } else {
                                * classIdx = 9;* classScore = 24.0;
                                return;
                            }
                        }
                    }
                } else {
                    if (x[3] < -37.5) {
                        if (x[0] < -74.5) {
                            if (x[0] < -82.5) {
                                if (x[5] < -89.5) {
                                    if (x[0] < -86.0) {
                                        * classIdx = 1;* classScore = 25.0;
                                        return;
                                    } else {
                                        * classIdx = 0;* classScore = 30.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 1;* classScore = 25.0;
                                    return;
                                }
                            } else {
                                if (x[8] < -76.5) {
                                    * classIdx = 1;* classScore = 25.0;
                                    return;
                                } else {
                                    * classIdx = 8;* classScore = 23.0;
                                    return;
                                }
                            }
                        } else {
                            if (x[2] < -34.0) {
                                * classIdx = 0;* classScore = 30.0;
                                return;
                            } else {
                                * classIdx = 8;* classScore = 23.0;
                                return;
                            }
                        }
                    } else {
                        if (x[5] < -90.5) {
                            if (x[4] < -44.0) {
                                * classIdx = 8;* classScore = 23.0;
                                return;
                            } else {
                                if (x[1] < -87.5) {
                                    * classIdx = 0;* classScore = 30.0;
                                    return;
                                } else {
                                    * classIdx = 8;* classScore = 23.0;
                                    return;
                                }
                            }
                        } else {
                            * classIdx = 8;* classScore = 23.0;
                            return;
                        }
                    }
                }
            } else {
                if (x[2] < -67.5) {
                    if (x[2] < -73.5) {
                        if (x[9] < -69.5) {
                            if (x[3] < -74.5) {
                                if (x[8] < -88.5) {
                                    if (x[5] < -62.0) {
                                        * classIdx = 4;* classScore = 40.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 24.0;
                                        return;
                                    }
                                } else {
                                    if (x[8] < -43.5) {
                                        * classIdx = 6;* classScore = 16.0;
                                        return;
                                    } else {
                                        * classIdx = 3;* classScore = 27.0;
                                        return;
                                    }
                                }
                            } else {
                                * classIdx = 4;* classScore = 40.0;
                                return;
                            }
                        } else {
                            if (x[5] < -62.5) {
                                if (x[9] < -67.5) {
                                    * classIdx = 5;* classScore = 24.0;
                                    return;
                                } else {
                                    * classIdx = 4;* classScore = 40.0;
                                    return;
                                }
                            } else {
                                * classIdx = 4;* classScore = 40.0;
                                return;
                            }
                        }
                    } else {
                        if (x[4] < -66.5) {
                            if (x[5] < -75.5) {
                                if (x[8] < -44.0) {
                                    * classIdx = 1;* classScore = 25.0;
                                    return;
                                } else {
                                    * classIdx = 3;* classScore = 27.0;
                                    return;
                                }
                            } else {
                                if (x[5] < -65.0) {
                                    if (x[9] < -77.0) {
                                        * classIdx = 6;* classScore = 16.0;
                                        return;
                                    } else {
                                        * classIdx = 9;* classScore = 24.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 6;* classScore = 16.0;
                                    return;
                                }
                            }
                        } else {
                            if (x[5] < -64.5) {
                                if (x[3] < -77.5) {
                                    * classIdx = 6;* classScore = 16.0;
                                    return;
                                } else {
                                    if (x[9] < -55.5) {
                                        * classIdx = 4;* classScore = 40.0;
                                        return;
                                    } else {
                                        * classIdx = 9;* classScore = 24.0;
                                        return;
                                    }
                                }
                            } else {
                                if (x[4] < -63.5) {
                                    if (x[3] < -80.0) {
                                        * classIdx = 5;* classScore = 24.0;
                                        return;
                                    } else {
                                        * classIdx = 4;* classScore = 40.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 4;* classScore = 40.0;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    if (x[4] < -71.5) {
                        if (x[9] < -85.5) {
                            if (x[2] < -65.5) {
                                * classIdx = 1;* classScore = 25.0;
                                return;
                            } else {
                                * classIdx = 2;* classScore = 19.0;
                                return;
                            }
                        } else {
                            if (x[5] < -76.5) {
                                * classIdx = 3;* classScore = 27.0;
                                return;
                            } else {
                                if (x[1] < -43.5) {
                                    * classIdx = 2;* classScore = 19.0;
                                    return;
                                } else {
                                    * classIdx = 9;* classScore = 24.0;
                                    return;
                                }
                            }
                        }
                    } else {
                        if (x[8] < -91.5) {
                            if (x[2] < -64.5) {
                                * classIdx = 5;* classScore = 24.0;
                                return;
                            } else {
                                * classIdx = 2;* classScore = 19.0;
                                return;
                            }
                        } else {
                            if (x[4] < -56.5) {
                                * classIdx = 9;* classScore = 24.0;
                                return;
                            } else {
                                if (x[9] < -57.0) {
                                    if (x[9] < -66.5) {
                                        * classIdx = 5;* classScore = 24.0;
                                        return;
                                    } else {
                                        * classIdx = 4;* classScore = 40.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 9;* classScore = 24.0;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    void tree3(float * x, uint8_t * classIdx, float * classScore) {
        if (x[4] < -25.0) {
            if (x[7] < -27.5) {
                * classIdx = 7;* classScore = 13.0;
                return;
            } else {
                if (x[9] < -72.5) {
                    if (x[5] < -77.0) {
                        if (x[4] < -85.0) {
                            if (x[9] < -92.0) {
                                * classIdx = 8;* classScore = 28.0;
                                return;
                            } else {
                                if (x[0] < -94.5) {
                                    * classIdx = 3;* classScore = 29.0;
                                    return;
                                } else {
                                    if (x[3] < -61.5) {
                                        * classIdx = 2;* classScore = 14.0;
                                        return;
                                    } else {
                                        * classIdx = 3;* classScore = 29.0;
                                        return;
                                    }
                                }
                            }
                        } else {
                            * classIdx = 3;* classScore = 29.0;
                            return;
                        }
                    } else {
                        if (x[3] < -74.0) {
                            if (x[3] < -83.5) {
                                if (x[8] < -36.0) {
                                    if (x[5] < -73.0) {
                                        * classIdx = 5;* classScore = 29.0;
                                        return;
                                    } else {
                                        * classIdx = 6;* classScore = 20.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 5;* classScore = 29.0;
                                    return;
                                }
                            } else {
                                if (x[2] < -73.5) {
                                    * classIdx = 5;* classScore = 29.0;
                                    return;
                                } else {
                                    * classIdx = 6;* classScore = 20.0;
                                    return;
                                }
                            }
                        } else {
                            if (x[0] < -44.5) {
                                if (x[5] < -64.0) {
                                    * classIdx = 2;* classScore = 14.0;
                                    return;
                                } else {
                                    * classIdx = 6;* classScore = 20.0;
                                    return;
                                }
                            } else {
                                if (x[4] < -67.0) {
                                    * classIdx = 6;* classScore = 20.0;
                                    return;
                                } else {
                                    * classIdx = 4;* classScore = 37.0;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    if (x[2] < -67.5) {
                        if (x[9] < -60.5) {
                            if (x[4] < -64.5) {
                                if (x[5] < -64.0) {
                                    if (x[5] < -73.5) {
                                        * classIdx = 3;* classScore = 29.0;
                                        return;
                                    } else {
                                        * classIdx = 9;* classScore = 32.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 5;* classScore = 29.0;
                                    return;
                                }
                            } else {
                                if (x[8] < -89.0) {
                                    if (x[9] < -68.5) {
                                        * classIdx = 5;* classScore = 29.0;
                                        return;
                                    } else {
                                        * classIdx = 4;* classScore = 37.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 4;* classScore = 37.0;
                                    return;
                                }
                            }
                        } else {
                            if (x[5] < -79.5) {
                                if (x[1] < -82.0) {
                                    * classIdx = 8;* classScore = 28.0;
                                    return;
                                } else {
                                    if (x[5] < -88.0) {
                                        * classIdx = 0;* classScore = 16.0;
                                        return;
                                    } else {
                                        * classIdx = 1;* classScore = 24.0;
                                        return;
                                    }
                                }
                            } else {
                                if (x[3] < -70.5) {
                                    * classIdx = 9;* classScore = 32.0;
                                    return;
                                } else {
                                    if (x[3] < -68.0) {
                                        * classIdx = 4;* classScore = 37.0;
                                        return;
                                    } else {
                                        * classIdx = 4;* classScore = 37.0;
                                        return;
                                    }
                                }
                            }
                        }
                    } else {
                        if (x[9] < -16.0) {
                            if (x[4] < -74.5) {
                                if (x[1] < -46.0) {
                                    * classIdx = 3;* classScore = 29.0;
                                    return;
                                } else {
                                    * classIdx = 5;* classScore = 29.0;
                                    return;
                                }
                            } else {
                                * classIdx = 9;* classScore = 32.0;
                                return;
                            }
                        } else {
                            if (x[4] < -91.5) {
                                * classIdx = 1;* classScore = 24.0;
                                return;
                            } else {
                                * classIdx = 8;* classScore = 28.0;
                                return;
                            }
                        }
                    }
                }
            }
        } else {
            if (x[3] < -37.5) {
                if (x[0] < -75.0) {
                    if (x[2] < -77.0) {
                        if (x[1] < -76.0) {
                            * classIdx = 8;* classScore = 28.0;
                            return;
                        } else {
                            if (x[3] < -84.5) {
                                * classIdx = 0;* classScore = 16.0;
                                return;
                            } else {
                                * classIdx = 1;* classScore = 24.0;
                                return;
                            }
                        }
                    } else {
                        if (x[2] < -66.5) {
                            * classIdx = 1;* classScore = 24.0;
                            return;
                        } else {
                            if (x[1] < -72.0) {
                                * classIdx = 2;* classScore = 14.0;
                                return;
                            } else {
                                * classIdx = 1;* classScore = 24.0;
                                return;
                            }
                        }
                    }
                } else {
                    if (x[2] < -64.5) {
                        if (x[0] < -33.0) {
                            if (x[3] < -76.0) {
                                * classIdx = 0;* classScore = 16.0;
                                return;
                            } else {
                                * classIdx = 1;* classScore = 24.0;
                                return;
                            }
                        } else {
                            * classIdx = 1;* classScore = 24.0;
                            return;
                        }
                    } else {
                        if (x[8] < -87.5) {
                            * classIdx = 2;* classScore = 14.0;
                            return;
                        } else {
                            * classIdx = 8;* classScore = 28.0;
                            return;
                        }
                    }
                }
            } else {
                if (x[1] < -86.5) {
                    if (x[0] < -77.5) {
                        * classIdx = 8;* classScore = 28.0;
                        return;
                    } else {
                        if (x[2] < -90.5) {
                            * classIdx = 8;* classScore = 28.0;
                            return;
                        } else {
                            * classIdx = 0;* classScore = 16.0;
                            return;
                        }
                    }
                } else {
                    * classIdx = 8;* classScore = 28.0;
                    return;
                }
            }
        }
    }
    void tree4(float * x, uint8_t * classIdx, float * classScore) {
        if (x[5] < -74.0) {
            if (x[8] < -31.0) {
                if (x[6] < -32.5) {
                    * classIdx = 7;* classScore = 11.0;
                    return;
                } else {
                    if (x[8] < -74.5) {
                        if (x[2] < -65.5) {
                            if (x[8] < -82.0) {
                                if (x[5] < -90.5) {
                                    if (x[3] < -83.0) {
                                        * classIdx = 1;* classScore = 20.0;
                                        return;
                                    } else {
                                        * classIdx = 0;* classScore = 28.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 1;* classScore = 20.0;
                                    return;
                                }
                            } else {
                                if (x[1] < -86.0) {
                                    * classIdx = 8;* classScore = 30.0;
                                    return;
                                } else {
                                    if (x[2] < -85.0) {
                                        * classIdx = 8;* classScore = 30.0;
                                        return;
                                    } else {
                                        * classIdx = 0;* classScore = 28.0;
                                        return;
                                    }
                                }
                            }
                        } else {
                            if (x[5] < -89.0) {
                                * classIdx = 2;* classScore = 26.0;
                                return;
                            } else {
                                * classIdx = 1;* classScore = 20.0;
                                return;
                            }
                        }
                    } else {
                        if (x[0] < -69.5) {
                            * classIdx = 8;* classScore = 30.0;
                            return;
                        } else {
                            * classIdx = 0;* classScore = 28.0;
                            return;
                        }
                    }
                }
            } else {
                if (x[9] < -85.5) {
                    if (x[5] < -86.5) {
                        * classIdx = 3;* classScore = 25.0;
                        return;
                    } else {
                        * classIdx = 2;* classScore = 26.0;
                        return;
                    }
                } else {
                    if (x[1] < -85.0) {
                        * classIdx = 3;* classScore = 25.0;
                        return;
                    } else {
                        if (x[0] < -42.5) {
                            if (x[2] < -57.5) {
                                if (x[1] < -78.5) {
                                    * classIdx = 1;* classScore = 20.0;
                                    return;
                                } else {
                                    if (x[9] < -38.5) {
                                        * classIdx = 2;* classScore = 26.0;
                                        return;
                                    } else {
                                        * classIdx = 1;* classScore = 20.0;
                                        return;
                                    }
                                }
                            } else {
                                * classIdx = 3;* classScore = 25.0;
                                return;
                            }
                        } else {
                            if (x[9] < -83.0) {
                                * classIdx = 2;* classScore = 26.0;
                                return;
                            } else {
                                if (x[2] < -72.0) {
                                    * classIdx = 3;* classScore = 25.0;
                                    return;
                                } else {
                                    if (x[3] < -70.5) {
                                        * classIdx = 9;* classScore = 24.0;
                                        return;
                                    } else {
                                        * classIdx = 3;* classScore = 25.0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (x[5] < -24.5) {
                if (x[2] < -67.5) {
                    if (x[9] < -74.5) {
                        if (x[9] < -86.5) {
                            if (x[8] < -38.0) {
                                * classIdx = 6;* classScore = 24.0;
                                return;
                            } else {
                                * classIdx = 4;* classScore = 32.0;
                                return;
                            }
                        } else {
                            if (x[8] < -88.5) {
                                if (x[3] < -85.5) {
                                    if (x[2] < -76.0) {
                                        * classIdx = 5;* classScore = 22.0;
                                        return;
                                    } else {
                                        * classIdx = 6;* classScore = 24.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 5;* classScore = 22.0;
                                    return;
                                }
                            } else {
                                if (x[5] < -54.0) {
                                    if (x[2] < -75.0) {
                                        * classIdx = 6;* classScore = 24.0;
                                        return;
                                    } else {
                                        * classIdx = 6;* classScore = 24.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 5;* classScore = 22.0;
                                    return;
                                }
                            }
                        }
                    } else {
                        if (x[4] < -72.5) {
                            if (x[0] < -44.5) {
                                * classIdx = 5;* classScore = 22.0;
                                return;
                            } else {
                                * classIdx = 9;* classScore = 24.0;
                                return;
                            }
                        } else {
                            if (x[8] < -91.5) {
                                if (x[2] < -77.5) {
                                    if (x[8] < -92.5) {
                                        * classIdx = 5;* classScore = 22.0;
                                        return;
                                    } else {
                                        * classIdx = 4;* classScore = 32.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 5;* classScore = 22.0;
                                    return;
                                }
                            } else {
                                if (x[3] < -78.0) {
                                    if (x[4] < -62.0) {
                                        * classIdx = 5;* classScore = 22.0;
                                        return;
                                    } else {
                                        * classIdx = 4;* classScore = 32.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 4;* classScore = 32.0;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    if (x[3] < -62.0) {
                        if (x[0] < -46.5) {
                            * classIdx = 5;* classScore = 22.0;
                            return;
                        } else {
                            * classIdx = 9;* classScore = 24.0;
                            return;
                        }
                    } else {
                        if (x[9] < -69.5) {
                            * classIdx = 6;* classScore = 24.0;
                            return;
                        } else {
                            * classIdx = 4;* classScore = 32.0;
                            return;
                        }
                    }
                }
            } else {
                if (x[2] < -32.5) {
                    if (x[3] < -90.5) {
                        * classIdx = 8;* classScore = 30.0;
                        return;
                    } else {
                        * classIdx = 0;* classScore = 28.0;
                        return;
                    }
                } else {
                    * classIdx = 8;* classScore = 30.0;
                    return;
                }
            }
        }
    } /** * Random forest's tree #5 */
    void tree5(float * x, uint8_t * classIdx, float * classScore) {
        if (x[9] < -16.0) {
            if (x[5] < -73.5) {
                if (x[9] < -82.5) {
                    if (x[9] < -90.5) {
                        if (x[6] < -36.0) {
                            * classIdx = 7;* classScore = 19.0;
                            return;
                        } else {
                            if (x[3] < -88.0) {
                                * classIdx = 8;* classScore = 22.0;
                                return;
                            } else {
                                * classIdx = 1;* classScore = 20.0;
                                return;
                            }
                        }
                    } else {
                        if (x[1] < -84.5) {
                            * classIdx = 3;* classScore = 25.0;
                            return;
                        } else {
                            if (x[2] < -75.5) {
                                * classIdx = 5;* classScore = 22.0;
                                return;
                            } else {
                                if (x[0] < -86.0) {
                                    * classIdx = 2;* classScore = 17.0;
                                    return;
                                } else {
                                    if (x[5] < -83.5) {
                                        * classIdx = 2;* classScore = 17.0;
                                        return;
                                    } else {
                                        * classIdx = 1;* classScore = 20.0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (x[9] < -62.0) {
                        if (x[5] < -76.0) {
                            * classIdx = 3;* classScore = 25.0;
                            return;
                        } else {
                            if (x[3] < -69.5) {
                                * classIdx = 3;* classScore = 25.0;
                                return;
                            } else {
                                * classIdx = 2;* classScore = 17.0;
                                return;
                            }
                        }
                    } else {
                        * classIdx = 9;* classScore = 33.0;
                        return;
                    }
                }
            } else {
                if (x[9] < -72.5) {
                    if (x[0] < -88.5) {
                        if (x[0] < -90.5) {
                            * classIdx = 5;* classScore = 22.0;
                            return;
                        } else {
                            * classIdx = 6;* classScore = 19.0;
                            return;
                        }
                    } else {
                        if (x[8] < -91.5) {
                            * classIdx = 5;* classScore = 22.0;
                            return;
                        } else {
                            if (x[5] < -57.5) {
                                if (x[4] < -61.5) {
                                    if (x[1] < -40.0) {
                                        * classIdx = 6;* classScore = 19.0;
                                        return;
                                    } else {
                                        * classIdx = 6;* classScore = 19.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 4;* classScore = 35.0;
                                    return;
                                }
                            } else {
                                * classIdx = 5;* classScore = 22.0;
                                return;
                            }
                        }
                    }
                } else {
                    if (x[2] < -67.5) {
                        if (x[1] < -43.0) {
                            if (x[8] < -91.5) {
                                * classIdx = 5;* classScore = 22.0;
                                return;
                            } else {
                                * classIdx = 9;* classScore = 33.0;
                                return;
                            }
                        } else {
                            if (x[9] < -57.5) {
                                if (x[2] < -73.5) {
                                    * classIdx = 4;* classScore = 35.0;
                                    return;
                                } else {
                                    if (x[8] < -43.0) {
                                        * classIdx = 4;* classScore = 35.0;
                                        return;
                                    } else {
                                        * classIdx = 4;* classScore = 35.0;
                                        return;
                                    }
                                }
                            } else {
                                * classIdx = 9;* classScore = 33.0;
                                return;
                            }
                        }
                    } else {
                        if (x[4] < -74.5) {
                            * classIdx = 5;* classScore = 22.0;
                            return;
                        } else {
                            * classIdx = 9;* classScore = 33.0;
                            return;
                        }
                    }
                }
            }
        } else {
            if (x[8] < -74.5) {
                if (x[4] < -35.0) {
                    if (x[7] < -27.5) {
                        * classIdx = 7;* classScore = 19.0;
                        return;
                    } else {
                        if (x[8] < -83.0) {
                            * classIdx = 1;* classScore = 20.0;
                            return;
                        } else {
                            * classIdx = 0;* classScore = 30.0;
                            return;
                        }
                    }
                } else {
                    if (x[2] < -75.5) {
                        if (x[0] < -79.5) {
                            if (x[2] < -82.0) {
                                * classIdx = 1;* classScore = 20.0;
                                return;
                            } else {
                                * classIdx = 8;* classScore = 22.0;
                                return;
                            }
                        } else {
                            * classIdx = 0;* classScore = 30.0;
                            return;
                        }
                    } else {
                        if (x[0] < -76.0) {
                            if (x[2] < -73.5) {
                                if (x[0] < -86.5) {
                                    * classIdx = 1;* classScore = 20.0;
                                    return;
                                } else {
                                    * classIdx = 0;* classScore = 30.0;
                                    return;
                                }
                            } else {
                                * classIdx = 1;* classScore = 20.0;
                                return;
                            }
                        } else {
                            if (x[2] < -73.5) {
                                * classIdx = 1;* classScore = 20.0;
                                return;
                            } else {
                                * classIdx = 0;* classScore = 30.0;
                                return;
                            }
                        }
                    }
                }
            } else {
                if (x[8] < -29.5) {
                    if (x[1] < -87.0) {
                        * classIdx = 8;* classScore = 22.0;
                        return;
                    } else {
                        if (x[8] < -71.0) {
                            * classIdx = 0;* classScore = 30.0;
                            return;
                        } else {
                            if (x[5] < -44.5) {
                                * classIdx = 8;* classScore = 22.0;
                                return;
                            } else {
                                if (x[0] < -73.5) {
                                    * classIdx = 8;* classScore = 22.0;
                                    return;
                                } else {
                                    * classIdx = 0;* classScore = 30.0;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    if (x[3] < -80.0) {
                        if (x[0] < -91.5) {
                            * classIdx = 2;* classScore = 17.0;
                            return;
                        } else {
                            * classIdx = 1;* classScore = 20.0;
                            return;
                        }
                    } else {
                        * classIdx = 1;* classScore = 20.0;
                        return;
                    }
                }
            }
        }
    }
    void tree6(float * x, uint8_t * classIdx, float * classScore) {
        if (x[4] < -22.0) {
            if (x[1] < -33.5) {
                if (x[5] < -70.5) {
                    if (x[4] < -83.5) {
                        if (x[9] < -80.5) {
                            if (x[1] < -80.5) {
                                if (x[2] < -63.0) {
                                    * classIdx = 3;* classScore = 31.0;
                                    return;
                                } else {
                                    * classIdx = 2;* classScore = 18.0;
                                    return;
                                }
                            } else {
                                if (x[3] < -79.5) {
                                    * classIdx = 2;* classScore = 18.0;
                                    return;
                                } else {
                                    if (x[5] < -81.0) {
                                        * classIdx = 2;* classScore = 18.0;
                                        return;
                                    } else {
                                        * classIdx = 1;* classScore = 16.0;
                                        return;
                                    }
                                }
                            }
                        } else {
                            if (x[4] < -91.5) {
                                if (x[5] < -89.5) {
                                    * classIdx = 0;* classScore = 29.0;
                                    return;
                                } else {
                                    * classIdx = 1;* classScore = 16.0;
                                    return;
                                }
                            } else {
                                if (x[9] < -35.5) {
                                    * classIdx = 3;* classScore = 31.0;
                                    return;
                                } else {
                                    if (x[8] < -75.0) {
                                        * classIdx = 7;* classScore = 14.0;
                                        return;
                                    } else {
                                        * classIdx = 8;* classScore = 25.0;
                                        return;
                                    }
                                }
                            }
                        }
                    } else {
                        if (x[6] < -36.0) {
                            * classIdx = 7;* classScore = 14.0;
                            return;
                        } else {
                            * classIdx = 3;* classScore = 31.0;
                            return;
                        }
                    }
                } else {
                    if (x[4] < -73.5) {
                        * classIdx = 6;* classScore = 23.0;
                        return;
                    } else {
                        if (x[2] < -73.5) {
                            if (x[1] < -82.0) {
                                * classIdx = 5;* classScore = 24.0;
                                return;
                            } else {
                                if (x[9] < -83.0) {
                                    * classIdx = 5;* classScore = 24.0;
                                    return;
                                } else {
                                    * classIdx = 6;* classScore = 23.0;
                                    return;
                                }
                            }
                        } else {
                            * classIdx = 9;* classScore = 25.0;
                            return;
                        }
                    }
                }
            } else {
                if (x[4] < -62.0) {
                    if (x[8] < -84.0) {
                        if (x[6] < -36.5) {
                            * classIdx = 7;* classScore = 14.0;
                            return;
                        } else {
                            if (x[5] < -62.0) {
                                if (x[4] < -73.5) {
                                    * classIdx = 5;* classScore = 24.0;
                                    return;
                                } else {
                                    if (x[9] < -78.5) {
                                        * classIdx = 6;* classScore = 23.0;
                                        return;
                                    } else {
                                        * classIdx = 4;* classScore = 37.0;
                                        return;
                                    }
                                }
                            } else {
                                if (x[9] < -78.5) {
                                    * classIdx = 5;* classScore = 24.0;
                                    return;
                                } else {
                                    if (x[5] < -58.0) {
                                        * classIdx = 5;* classScore = 24.0;
                                        return;
                                    } else {
                                        * classIdx = 6;* classScore = 23.0;
                                        return;
                                    }
                                }
                            }
                        }
                    } else {
                        if (x[6] < -34.0) {
                            * classIdx = 7;* classScore = 14.0;
                            return;
                        } else {
                            if (x[3] < -81.5) {
                                if (x[8] < -70.5) {
                                    * classIdx = 6;* classScore = 23.0;
                                    return;
                                } else {
                                    if (x[0] < -41.0) {
                                        * classIdx = 5;* classScore = 24.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 24.0;
                                        return;
                                    }
                                }
                            } else {
                                if (x[0] < -44.5) {
                                    * classIdx = 2;* classScore = 18.0;
                                    return;
                                } else {
                                    if (x[4] < -70.0) {
                                        * classIdx = 9;* classScore = 25.0;
                                        return;
                                    } else {
                                        * classIdx = 4;* classScore = 37.0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (x[3] < -84.5) {
                        * classIdx = 6;* classScore = 23.0;
                        return;
                    } else {
                        if (x[3] < -79.5) {
                            if (x[2] < -77.0) {
                                * classIdx = 4;* classScore = 37.0;
                                return;
                            } else {
                                * classIdx = 5;* classScore = 24.0;
                                return;
                            }
                        } else {
                            * classIdx = 4;* classScore = 37.0;
                            return;
                        }
                    }
                }
            }
        } else {
            if (x[8] < -72.0) {
                if (x[0] < -76.5) {
                    if (x[5] < -89.0) {
                        if (x[2] < -83.0) {
                            if (x[5] < -91.5) {
                                * classIdx = 8;* classScore = 25.0;
                                return;
                            } else {
                                * classIdx = 0;* classScore = 29.0;
                                return;
                            }
                        } else {
                            if (x[1] < -72.0) {
                                if (x[1] < -76.0) {
                                    * classIdx = 1;* classScore = 16.0;
                                    return;
                                } else {
                                    * classIdx = 0;* classScore = 29.0;
                                    return;
                                }
                            } else {
                                * classIdx = 1;* classScore = 16.0;
                                return;
                            }
                        }
                    } else {
                        * classIdx = 8;* classScore = 25.0;
                        return;
                    }
                } else {
                    if (x[3] < -91.5) {
                        * classIdx = 8;* classScore = 25.0;
                        return;
                    } else {
                        if (x[2] < -91.0) {
                            * classIdx = 8;* classScore = 25.0;
                            return;
                        } else {
                            if (x[1] < -67.5) {
                                if (x[1] < -79.5) {
                                    if (x[1] < -83.5) {
                                        * classIdx = 0;* classScore = 29.0;
                                        return;
                                    } else {
                                        * classIdx = 2;* classScore = 18.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 0;* classScore = 29.0;
                                    return;
                                }
                            } else {
                                * classIdx = 1;* classScore = 16.0;
                                return;
                            }
                        }
                    }
                }
            } else {
                if (x[8] < -31.0) {
                    * classIdx = 8;* classScore = 25.0;
                    return;
                } else {
                    if (x[1] < -80.5) {
                        * classIdx = 1;* classScore = 16.0;
                        return;
                    } else {
                        * classIdx = 2;* classScore = 18.0;
                        return;
                    }
                }
            }
        }
    }
    void tree7(float * x, uint8_t * classIdx, float * classScore) {
        if (x[5] < -74.5) {
            if (x[8] < -31.0) {
                if (x[7] < -27.5) {
                    * classIdx = 7;* classScore = 15.0;
                    return;
                } else {
                    if (x[3] < -35.5) {
                        if (x[0] < -76.5) {
                            if (x[1] < -79.0) {
                                if (x[0] < -83.5) {
                                    * classIdx = 2;* classScore = 25.0;
                                    return;
                                } else {
                                    * classIdx = 8;* classScore = 27.0;
                                    return;
                                }
                            } else {
                                if (x[5] < -78.5) {
                                    * classIdx = 1;* classScore = 17.0;
                                    return;
                                } else {
                                    * classIdx = 5;* classScore = 29.0;
                                    return;
                                }
                            }
                        } else {
                            if (x[2] < -75.5) {
                                * classIdx = 0;* classScore = 23.0;
                                return;
                            } else {
                                if (x[1] < -78.5) {
                                    if (x[0] < -33.5) {
                                        * classIdx = 0;* classScore = 23.0;
                                        return;
                                    } else {
                                        * classIdx = 2;* classScore = 25.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 1;* classScore = 17.0;
                                    return;
                                }
                            }
                        }
                    } else {
                        if (x[1] < -88.5) {
                            if (x[5] < -90.5) {
                                * classIdx = 0;* classScore = 23.0;
                                return;
                            } else {
                                * classIdx = 8;* classScore = 27.0;
                                return;
                            }
                        } else {
                            * classIdx = 8;* classScore = 27.0;
                            return;
                        }
                    }
                }
            } else {
                if (x[4] < -88.5) {
                    * classIdx = 2;* classScore = 25.0;
                    return;
                } else {
                    if (x[3] < -81.5) {
                        * classIdx = 2;* classScore = 25.0;
                        return;
                    } else {
                        if (x[0] < -42.5) {
                            * classIdx = 1;* classScore = 17.0;
                            return;
                        } else {
                            if (x[4] < -34.0) {
                                if (x[9] < -88.5) {
                                    * classIdx = 2;* classScore = 25.0;
                                    return;
                                } else {
                                    if (x[9] < -75.5) {
                                        * classIdx = 3;* classScore = 29.0;
                                        return;
                                    } else {
                                        * classIdx = 3;* classScore = 29.0;
                                        return;
                                    }
                                }
                            } else {
                                * classIdx = 2;* classScore = 25.0;
                                return;
                            }
                        }
                    }
                }
            }
        } else {
            if (x[3] < -74.5) {
                if (x[9] < -61.5) {
                    if (x[5] < -66.5) {
                        if (x[3] < -86.0) {
                            * classIdx = 6;* classScore = 24.0;
                            return;
                        } else {
                            if (x[2] < -76.5) {
                                * classIdx = 5;* classScore = 29.0;
                                return;
                            } else {
                                * classIdx = 6;* classScore = 24.0;
                                return;
                            }
                        }
                    } else {
                        if (x[2] < -73.5) {
                            if (x[0] < -89.5) {
                                * classIdx = 5;* classScore = 29.0;
                                return;
                            } else {
                                if (x[4] < -73.5) {
                                    * classIdx = 6;* classScore = 24.0;
                                    return;
                                } else {
                                    if (x[2] < -77.5) {
                                        * classIdx = 4;* classScore = 39.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 29.0;
                                        return;
                                    }
                                }
                            }
                        } else {
                            if (x[9] < -77.5) {
                                if (x[9] < -82.5) {
                                    if (x[4] < -71.5) {
                                        * classIdx = 5;* classScore = 29.0;
                                        return;
                                    } else {
                                        * classIdx = 6;* classScore = 24.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 6;* classScore = 24.0;
                                    return;
                                }
                            } else {
                                * classIdx = 5;* classScore = 29.0;
                                return;
                            }
                        }
                    }
                } else {
                    if (x[4] < -35.0) {
                        if (x[4] < -72.5) {
                            * classIdx = 9;* classScore = 14.0;
                            return;
                        } else {
                            * classIdx = 7;* classScore = 15.0;
                            return;
                        }
                    } else {
                        if (x[8] < -73.5) {
                            * classIdx = 0;* classScore = 23.0;
                            return;
                        } else {
                            if (x[2] < -78.5) {
                                * classIdx = 8;* classScore = 27.0;
                                return;
                            } else {
                                if (x[3] < -88.0) {
                                    * classIdx = 8;* classScore = 27.0;
                                    return;
                                } else {
                                    * classIdx = 0;* classScore = 23.0;
                                    return;
                                }
                            }
                        }
                    }
                }
            } else {
                if (x[5] < -26.5) {
                    if (x[4] < -70.5) {
                        if (x[2] < -66.5) {
                            * classIdx = 6;* classScore = 24.0;
                            return;
                        } else {
                            * classIdx = 9;* classScore = 14.0;
                            return;
                        }
                    } else {
                        if (x[9] < -58.0) {
                            if (x[2] < -71.5) {
                                * classIdx = 4;* classScore = 39.0;
                                return;
                            } else {
                                if (x[8] < -88.5) {
                                    if (x[3] < -69.0) {
                                        * classIdx = 4;* classScore = 39.0;
                                        return;
                                    } else {
                                        * classIdx = 9;* classScore = 14.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 4;* classScore = 39.0;
                                    return;
                                }
                            }
                        } else {
                            * classIdx = 9;* classScore = 14.0;
                            return;
                        }
                    }
                } else {
                    if (x[8] < -72.5) {
                        if (x[0] < -72.5) {
                            * classIdx = 7;* classScore = 15.0;
                            return;
                        } else {
                            * classIdx = 0;* classScore = 23.0;
                            return;
                        }
                    } else {
                        * classIdx = 8;* classScore = 27.0;
                        return;
                    }
                }
            }
        }
    }
    void tree8(float * x, uint8_t * classIdx, float * classScore) {
        if (x[9] < -16.0) {
            if (x[9] < -70.5) {
                if (x[5] < -75.5) {
                    if (x[3] < -68.0) {
                        if (x[3] < -88.0) {
                            * classIdx = 8;* classScore = 35.0;
                            return;
                        } else {
                            if (x[5] < -85.5) {
                                if (x[4] < -90.5) {
                                    * classIdx = 1;* classScore = 28.0;
                                    return;
                                } else {
                                    if (x[9] < -88.5) {
                                        * classIdx = 1;* classScore = 28.0;
                                        return;
                                    } else {
                                        * classIdx = 3;* classScore = 27.0;
                                        return;
                                    }
                                }
                            } else {
                                if (x[3] < -86.5) {
                                    * classIdx = 1;* classScore = 28.0;
                                    return;
                                } else {
                                    if (x[5] < -80.5) {
                                        * classIdx = 2;* classScore = 13.0;
                                        return;
                                    } else {
                                        * classIdx = 2;* classScore = 13.0;
                                        return;
                                    }
                                }
                            }
                        }
                    } else {
                        if (x[3] < -21.0) {
                            * classIdx = 3;* classScore = 27.0;
                            return;
                        } else {
                            * classIdx = 7;* classScore = 15.0;
                            return;
                        }
                    }
                } else {
                    if (x[3] < -85.5) {
                        if (x[3] < -88.5) {
                            if (x[4] < -78.5) {
                                * classIdx = 5;* classScore = 27.0;
                                return;
                            } else {
                                * classIdx = 6;* classScore = 20.0;
                                return;
                            }
                        } else {
                            * classIdx = 6;* classScore = 20.0;
                            return;
                        }
                    } else {
                        if (x[3] < -74.5) {
                            if (x[5] < -64.0) {
                                * classIdx = 6;* classScore = 20.0;
                                return;
                            } else {
                                if (x[1] < -79.5) {
                                    if (x[4] < -72.0) {
                                        * classIdx = 6;* classScore = 20.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 27.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 5;* classScore = 27.0;
                                    return;
                                }
                            }
                        } else {
                            if (x[2] < -71.5) {
                                * classIdx = 4;* classScore = 30.0;
                                return;
                            } else {
                                * classIdx = 6;* classScore = 20.0;
                                return;
                            }
                        }
                    }
                }
            } else {
                if (x[3] < -65.5) {
                    if (x[9] < -62.5) {
                        if (x[4] < -69.0) {
                            if (x[3] < -75.5) {
                                * classIdx = 5;* classScore = 27.0;
                                return;
                            } else {
                                * classIdx = 3;* classScore = 27.0;
                                return;
                            }
                        } else {
                            if (x[1] < -43.0) {
                                * classIdx = 5;* classScore = 27.0;
                                return;
                            } else {
                                * classIdx = 4;* classScore = 30.0;
                                return;
                            }
                        }
                    } else {
                        if (x[4] < -68.5) {
                            * classIdx = 9;* classScore = 24.0;
                            return;
                        } else {
                            if (x[9] < -48.5) {
                                * classIdx = 4;* classScore = 30.0;
                                return;
                            } else {
                                * classIdx = 9;* classScore = 24.0;
                                return;
                            }
                        }
                    }
                } else {
                    if (x[2] < -71.5) {
                        if (x[2] < -72.5) {
                            * classIdx = 3;* classScore = 27.0;
                            return;
                        } else {
                            * classIdx = 4;* classScore = 30.0;
                            return;
                        }
                    } else {
                        if (x[2] < -62.0) {
                            * classIdx = 9;* classScore = 24.0;
                            return;
                        } else {
                            * classIdx = 4;* classScore = 30.0;
                            return;
                        }
                    }
                }
            }
        } else {
            if (x[7] < -27.5) {
                * classIdx = 7;* classScore = 15.0;
                return;
            } else {
                if (x[0] < -73.5) {
                    if (x[2] < -79.5) {
                        if (x[8] < -83.5) {
                            if (x[8] < -86.5) {
                                * classIdx = 0;* classScore = 23.0;
                                return;
                            } else {
                                * classIdx = 1;* classScore = 28.0;
                                return;
                            }
                        } else {
                            * classIdx = 8;* classScore = 35.0;
                            return;
                        }
                    } else {
                        if (x[8] < -79.5) {
                            * classIdx = 1;* classScore = 28.0;
                            return;
                        } else {
                            if (x[8] < -32.0) {
                                if (x[0] < -84.0) {
                                    * classIdx = 0;* classScore = 23.0;
                                    return;
                                } else {
                                    * classIdx = 8;* classScore = 35.0;
                                    return;
                                }
                            } else {
                                if (x[2] < -66.5) {
                                    * classIdx = 1;* classScore = 28.0;
                                    return;
                                } else {
                                    * classIdx = 2;* classScore = 13.0;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    if (x[8] < -71.5) {
                        if (x[4] < -91.5) {
                            * classIdx = 1;* classScore = 28.0;
                            return;
                        } else {
                            if (x[1] < -75.5) {
                                * classIdx = 0;* classScore = 23.0;
                                return;
                            } else {
                                if (x[1] < -73.5) {
                                    if (x[2] < -77.0) {
                                        * classIdx = 0;* classScore = 23.0;
                                        return;
                                    } else {
                                        * classIdx = 1;* classScore = 28.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 0;* classScore = 23.0;
                                    return;
                                }
                            }
                        }
                    } else {
                        if (x[2] < -86.5) {
                            * classIdx = 8;* classScore = 35.0;
                            return;
                        } else {
                            if (x[3] < -41.5) {
                                * classIdx = 0;* classScore = 23.0;
                                return;
                            } else {
                                * classIdx = 8;* classScore = 35.0;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    void tree9(float * x, uint8_t * classIdx, float * classScore) {
        if (x[5] < -74.5) {
            if (x[0] < -31.5) {
                if (x[6] < -38.0) {
                    * classIdx = 7;* classScore = 6.0;
                    return;
                } else {
                    if (x[0] < -73.5) {
                        if (x[0] < -74.5) {
                            if (x[3] < -35.5) {
                                if (x[8] < -81.5) {
                                    if (x[5] < -80.5) {
                                        * classIdx = 1;* classScore = 22.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 37.0;
                                        return;
                                    }
                                } else {
                                    if (x[9] < -42.0) {
                                        * classIdx = 2;* classScore = 11.0;
                                        return;
                                    } else {
                                        * classIdx = 0;* classScore = 29.0;
                                        return;
                                    }
                                }
                            } else {
                                if (x[8] < -81.0) {
                                    * classIdx = 0;* classScore = 29.0;
                                    return;
                                } else {
                                    * classIdx = 8;* classScore = 26.0;
                                    return;
                                }
                            }
                        } else {
                            * classIdx = 8;* classScore = 26.0;
                            return;
                        }
                    } else {
                        if (x[8] < -70.5) {
                            * classIdx = 0;* classScore = 29.0;
                            return;
                        } else {
                            * classIdx = 8;* classScore = 26.0;
                            return;
                        }
                    }
                }
            } else {
                if (x[8] < -45.0) {
                    if (x[1] < -40.5) {
                        * classIdx = 2;* classScore = 11.0;
                        return;
                    } else {
                        * classIdx = 7;* classScore = 6.0;
                        return;
                    }
                } else {
                    if (x[9] < -86.0) {
                        if (x[3] < -59.5) {
                            if (x[4] < -90.5) {
                                if (x[9] < -88.0) {
                                    * classIdx = 1;* classScore = 22.0;
                                    return;
                                } else {
                                    * classIdx = 2;* classScore = 11.0;
                                    return;
                                }
                            } else {
                                * classIdx = 2;* classScore = 11.0;
                                return;
                            }
                        } else {
                            * classIdx = 3;* classScore = 29.0;
                            return;
                        }
                    } else {
                        if (x[1] < -84.5) {
                            * classIdx = 3;* classScore = 29.0;
                            return;
                        } else {
                            if (x[4] < -89.0) {
                                * classIdx = 2;* classScore = 11.0;
                                return;
                            } else {
                                if (x[4] < -81.5) {
                                    * classIdx = 3;* classScore = 29.0;
                                    return;
                                } else {
                                    if (x[3] < -70.5) {
                                        * classIdx = 3;* classScore = 29.0;
                                        return;
                                    } else {
                                        * classIdx = 3;* classScore = 29.0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (x[9] < -72.5) {
                if (x[2] < -79.0) {
                    if (x[8] < -88.5) {
                        if (x[1] < -39.5) {
                            * classIdx = 5;* classScore = 37.0;
                            return;
                        } else {
                            * classIdx = 6;* classScore = 15.0;
                            return;
                        }
                    } else {
                        * classIdx = 6;* classScore = 15.0;
                        return;
                    }
                } else {
                    if (x[3] < -74.5) {
                        if (x[9] < -87.5) {
                            * classIdx = 6;* classScore = 15.0;
                            return;
                        } else {
                            if (x[1] < -40.0) {
                                if (x[3] < -80.0) {
                                    * classIdx = 6;* classScore = 15.0;
                                    return;
                                } else {
                                    * classIdx = 5;* classScore = 37.0;
                                    return;
                                }
                            } else {
                                * classIdx = 5;* classScore = 37.0;
                                return;
                            }
                        }
                    } else {
                        * classIdx = 4;* classScore = 44.0;
                        return;
                    }
                }
            } else {
                if (x[4] < -24.0) {
                    if (x[1] < -43.5) {
                        if (x[8] < -91.5) {
                            * classIdx = 5;* classScore = 37.0;
                            return;
                        } else {
                            if (x[4] < -82.5) {
                                * classIdx = 8;* classScore = 26.0;
                                return;
                            } else {
                                * classIdx = 9;* classScore = 23.0;
                                return;
                            }
                        }
                    } else {
                        if (x[4] < -72.5) {
                            if (x[9] < -27.0) {
                                if (x[9] < -64.0) {
                                    * classIdx = 5;* classScore = 37.0;
                                    return;
                                } else {
                                    * classIdx = 9;* classScore = 23.0;
                                    return;
                                }
                            } else {
                                if (x[8] < -80.0) {
                                    * classIdx = 7;* classScore = 6.0;
                                    return;
                                } else {
                                    * classIdx = 8;* classScore = 26.0;
                                    return;
                                }
                            }
                        } else {
                            if (x[4] < -69.0) {
                                if (x[3] < -77.5) {
                                    * classIdx = 5;* classScore = 37.0;
                                    return;
                                } else {
                                    * classIdx = 4;* classScore = 44.0;
                                    return;
                                }
                            } else {
                                if (x[9] < -70.5) {
                                    if (x[5] < -57.5) {
                                        * classIdx = 4;* classScore = 44.0;
                                        return;
                                    } else {
                                        * classIdx = 5;* classScore = 37.0;
                                        return;
                                    }
                                } else {
                                    * classIdx = 4;* classScore = 44.0;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    if (x[1] < -36.5) {
                        if (x[8] < -67.0) {
                            * classIdx = 0;* classScore = 29.0;
                            return;
                        } else {
                            * classIdx = 8;* classScore = 26.0;
                            return;
                        }
                    } else {
                        * classIdx = 8;* classScore = 26.0;
                        return;
                    }
                }
            }
        }
    }
};
#endif
