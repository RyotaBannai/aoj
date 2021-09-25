{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module Queue where

import Common (readInputContest, readInputsTerm)

-- * ALDS1_3_B

type Process = [(String, Integer)]

type Completed = [(String, Integer)]

type Time = Integer

type Quantum = Integer

run :: (Process, Completed) -> Time -> Quantum -> Completed
run ([], c) _ _ = c
run ((name, rem) : ps, c) t q =
  if rem <= q
    then let done = rem + t in run (ps, (name, done) : c) done q
    else run (reverse ((name, (-) rem q) : reverse ps), c) (t + q) q

toInt :: String -> Integer
toInt = read :: String -> Integer

toTuple :: [String] -> (String, Integer)
toTuple [f, s] = (f, toInt s)

format :: Completed -> [String]
format = map (\(name, time) -> name ++ " " ++ show time) . reverse

main :: IO ()
main = do
  [ps, q] <- map toInt . words <$> getLine
  xs <- readInputsTerm
  mapM_ putStrLn $ format $ run (map (toTuple . words) xs, []) 0 q