{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module Queue where

import Common (readInputContest, readInputsTerm)

-- * ALDS1_3_B

type Process = [(String, Integer)]

type Completed = [(String, Integer)]

type Time = Integer

type Quantum = Integer

type State = (Process, Completed, Time)

run :: State -> Quantum -> Completed
run s q = go s
  where
    go ([], c, _) = c
    go ((name, rem) : ps, c, t)
      | rem <= q = let done = rem + t in go (ps, (name, done) : c, done)
      | otherwise = go (ps ++ [(name, (-) rem q)], c, t + q)

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
  mapM_ putStrLn $ format $ run (map (toTuple . words) xs, [], 0) q