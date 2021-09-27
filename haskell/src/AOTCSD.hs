{-# LANGUAGE ViewPatterns #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module AOTCSD where

type State = (Stack, Areas, Pos)

type Stack = [Int]

type Areas = [(Int, Int)]

type Pos = Int

run :: String -> State -> Areas
run [] (_, as, _) = as
run (x : xs) (stk, as, i)
  | x == '\\' = run xs (i : stk, as, i + 1)
  | x == '/' = case stk of
    (j : stk') ->
      let (as', as'') = span ((j <) . fst) as -- 反対側の岸との間にある池.
          s = i - j
          ss = sum $ map snd as'
       in run xs (stk', (j, s + ss) : as'', i + 1) -- 反対側の岸を大きい池の最左点とする.
    [] -> skip
  | otherwise = skip
  where
    skip = run xs (stk, as, i + 1)

format :: Areas -> [String]
format (reverse -> as) = let as' = map snd as in [show . sum $ as', unwords . map show $ length as' : as']

main :: IO ()
main = getLine >>= (\x -> mapM_ putStrLn $ format $ run x ([], [], 0))

{-
rabbisland's ans with foldl instead of recursion

import Control.Applicative ((<$>))
import Data.ByteString.Char8 (ByteString)
import qualified Data.ByteString.Char8 as B

main :: IO ()
main = solve <$> B.getLine >>= mapM_ putStrLn

solve :: ByteString -> [String]
solve = g . B.foldl' f (0, [], [])
  where f :: (Int, [Int], [(Int, Int)]) -> Char -> (Int, [Int], [(Int, Int)])
        f (i, st1, st2) x | x == '\\' = (i+1, i:st1, st2)
                          | x == '/' = case st1 of
                                        (j:st1') -> let s = i - j
                                                        (st2', st2'') = span ((j<) . fst) st2
                                                    in (i+1, st1', (j, (s + (sum . map snd) st2')):st2'')
                                        [] -> (i+1, st1, st2)
                          | otherwise = (i+1, st1, st2)
        g (_, _, xs) = let ys = map snd xs
                       in [(show . sum) ys, (unwords . map show . ((length ys):) . reverse) ys]

-}