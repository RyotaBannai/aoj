{-# LANGUAGE ViewPatterns #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module SeqQueue where

import Common (readInputContest, readInputsTerm)
import Data.Foldable (toList)
import qualified Data.Sequence as S

-- * ALDS1_3_B

-- Also checkout <https://blog.tiqwab.com/2016/07/16/haskell-aizu1.html>

type Process = S.Seq (String, Integer)

type Completed = S.Seq (String, Integer)

type Time = Integer

type Quantum = Integer

type State = (Process, Completed, Time)

run :: State -> Quantum -> Completed
run s q = go s
  where
    go :: State -> Completed
    go (S.viewl -> S.EmptyL, c, t) = c
    go (S.viewl -> (name, rem) S.:< ps, c, t) =
      if rem <= q
        then let done = rem + t in go (ps, c S.|> (name, done), done)
        else go (ps S.|> (name, (-) rem q), c, t + q)

toInt :: String -> Integer
toInt = read :: String -> Integer

toTuple :: [String] -> (String, Integer)
toTuple [f, s] = (f, toInt s)

format :: Completed -> [String]
format = toList . fmap (\(name, time) -> name ++ " " ++ show time) -- no need `toList` conversion with GHC 8.0 ~

main :: IO ()
main = do
  [ps, q] <- map toInt . words <$> getLine
  xs <- readInputsTerm
  mapM_ putStrLn $ format $ run (S.fromList . map (toTuple . words) $ xs, S.empty, 0) q